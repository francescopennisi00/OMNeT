#include "PollingMaster.h"
#include "ApplicationPacket_m.h"

Define_Module(PollingMaster);

void PollingMaster::initialize() {

    /**
     *
     * INIZIALLIZZAZIONE CODA DI SCHEDULAZIONE DELLE POLLING REQUEST
     *
     * Constructor. When comparator argument is nullptr, the queue will
     * act as FIFO, otherwise as priority queue.

       cPacketQueue(const char *name, Comparator *cmp) : cQueue(name, cmp) {}
     *
     **/

    //non ci importa del nome della coda (mettiamo 0 come primo parametro)
    //come funzione di comparazione per stabilire la priorita' di ordinamento della coda mettiamo poll_queue_comp
    pollQueue = cPacketQueue(0, poll_queue_comp);

    //la tabella dei flussi sara' data come parametro del modulo PollingMaster: questa e' un parametro di configurazione di rete
    flowTable = check_and_cast<FlowTableParameters *>(par("flowTable").objectValue()); //objectValue() torna un cObject*

    for(int i=0; i < flowTable->getFlowsArraySize(); i++) {
        cMessage *tmr = new cMessage("PollTimer");  //costruiamo un polling timer iniziale per ogni flusso
        tmr->setKind(i);  //setta un dato di uso interno (indice del flusso) per il timer (simile al dataset in HTML/CSS/JAVASCRIPT)

        //allo scattare del primo istante del periodo del flusso, inviamo allo stesso PollingMaster il timer che fa scattare
        //l'inserimento in coda della PollingRequest per il flusso stesso
        scheduleAt(flowTable->getFlows(i).period, tmr);
    }

    onGoingTransaction = false;  //inizializziamo il modulo con il canale vuoto (all'inizio non c'e' alcuna transazione in corso)

    trxno = 0; //inizializziamo il numero di transazione a 0 (poi, per ogni nuova transazione, sara' incrementato)

    //costruiamo il messaggio trxTimer per attendere fino ad un certo istante i PollingData dai nodi sollecitati dalla PollingRequest
    trxTimer = new cMessage("TrxTimer");

    sigTrxTime = registerSignal("TrxTime");
}

void PollingMaster::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {

        if(strcmp(msg->getName(), "PollTimer") == 0) {
  //il messaggio arrivato era un PollingTimer, dobbiamo far scattare la PollingRequest relativa al flusso associato al PollingTimer: la inseriamo in coda

            PollingRequest *pr = new PollingRequest("PollingRequest");
            int i = msg->getKind();  //ottengo l'indice del flusso associato al PollingTimer
            FlowTableEntry f = flowTable->getFlows(i);
            pr->setFlow(f.flow.c_str());
            pr->setRequestedFrames(f.burst);  //frame richieste in numero pari al burst del flusso nella tabella di forwarding

            //la priorita' (che determina la posizione in coda della PollingRequest) potremmo averla settarla in base alla Deadline Relativa (EDF)
            //o ad un altro algoritmo di scheduling, es. DM (basato sulla Deadline Assoluta)
            if(strcmp(par("schedPolicy").stringValue(), "DM") == 0) {
                pr->setPriority(f.deadline.inUnit(SimTimeUnit::SIMTIME_US));
            } else if (strcmp(par("schedPolicy").stringValue(), "EDF") == 0) {
                long d = (f.deadline+simTime()).inUnit(SimTimeUnit::SIMTIME_US);
                pr->setPriority(d);
            } else {  //schedulazione FIFO
                pr->setPriority(0); //schedulazione FIFO = priorita' uguale per tutti (per tutti a 0)
            }

            //a questo punto possiamo accodare la nostra PollingRequest, inserendo la destinazione (cioe' l'interfaccia Ethernet dell'host che dovra'
            //trasmettere il PollingData, ovvero quello di sorgente dei pacchetti del flusso), prelevata dalla tabella di forwarding, nelle control info
            DataControlInfo *ci = new DataControlInfo();
            ci->setDestination(f.addr.c_str());
            pr->setControlInfo(ci);
            pollQueue.insert(pr);  //in pratica, allo scattare del PollTimer, mettiamo in coda una nuova PollingRequest

            //se il canale è libero da altre transazioni trasmettiamo, altrimenti non facciamo niente
            sendNextPollRequest();

            //rischeduliamo il PollingTimer in base al periodo del flusso associato
            scheduleAt(simTime()+f.period, msg);
            return;


        } else if(strcmp(msg->getName(), "TrxTimer") == 0) {
            //il messaggio e' il timer di trasmissione scaduto (se e' arrivato vuol dire che e' scaduto il tempo riservato alla transazione relativa)

            EV_INFO << "Transazione non completata in tempo" << endl;
            onGoingTransaction = false;
            sendNextPollRequest();  //trasmettiamo una nuova polling request
            return;
        }

        //potrebbe sopraggiungere un pacchetto per cui il timer di trasmissione e' gia' scaduto a causa di ritardi, mentre aspetto un altro pacchetto
        //tuttavia, poiche' l'identificativo della transazione del pacchetto in arrivo sara' diverso rispetto a quello della nuova transazione in corso,
        //tale pacchetto verra' scartato (e' partito troppo tardi ed e' sopraggiunto quando il tempo riservato alla sua transazione era ormai esaurito)
    }



    //e' arrivato un pacchetto da sotto (non puo'essere arrivato da sopra perche' il modulo non ha gates verso l'alto)

    //al PollingMaster interessa il messaggio solo se e' un PollingData (assumendo che non abbia applicazioni, cioe' che per lui AppCount = 0)
    PollingData * pd = dynamic_cast<PollingData*>(msg);
    if(pd != nullptr) {
         if(pd->getTrxno() != trxno) { //la transazione relativa al PollingData ricevuto non e' quella corrente
             error("Pacchetto arrivato fuori tempo massimo");
         }

         //dobbiamo decapsulare il pacchetto arrivato dall'alto in una PollingData e inviarlo alla destinazione

         emit(sigTrxTime, simTime()-txTime); //emetto il segnale per la durata della transazione

         //estraiamo dal PollingData il pacchetto applicativo da inviare (a livello piu' basso, quello dell'EthernetDataLink, oltre il Dispatcher,
         //si lavora con cPacket, ecco perche' to_send lo dichiaro cPacket * e non DataPacket *, nonostante sia un pacchetto dati applicativo)
         cPacket * to_send = pd->decapsulate();
         DataControlInfo *ci = new DataControlInfo();
         ci->setDestination(pd->getDestination());
         to_send->setControlInfo(ci);
         if(pd->getLast()) {
             //essendo arrivato l'ultimo PollingData del burst, non c'e' piu' alcuna transazione in corso (fino alla trasmissione della prossima PollRequest)
             onGoingTransaction = false;
             //elimino dalla coda degli eventi schedulati il timer di transazione perche' la transazione corrente e' stata correttamente completata
             //quindi si deve evitare la scadenza di tale timer, che se scade vuol dire che la transazione non e' stata completata in tempo
             cancelEvent(trxTimer);
         }
         delete pd; //non ci serve piu' il PollingData
         send(to_send, "lowerLayerOut");  //inviamo il pacchetto applicativo al livello inferiore: verra' consegnato al nodo di destinazione
         sendNextPollRequest(); //invio la successiva polling request, se il canale è libero da altre transazioni
         return;
    }

    //se il pacchetto arrivato non era un PollingData, non interessa al modulo PollingMaster ed e' pertanto eliminato
    delete msg;
}

//ad ogni nuovo evento, questa funzione viene richiamata, pertanto il Polling Master continuamente tentera' di trasmettere PollingRequest
//il timer PollTimer serve solo a dettare l'inserimento di una nuova PollingRequest nella coda, non a dettare l'istante di invio di una nuova PollingRequest,
//che avviene ad ogni nuovo evento (di fatto, continuamente) a patto che la coda non sia vuota e che non ci sia un'altra transazione in corso
void PollingMaster::sendNextPollRequest() {
    if(!onGoingTransaction && !pollQueue.isEmpty()) {
        onGoingTransaction = true; //sto avviando una transazione di una polling request
        PollingRequest * pr = check_and_cast<PollingRequest*>(pollQueue.pop());  //estraggo la prossima PollingRequest (quella a priorita' piu' alta)
        trxno++;  //avanzamento del numero di transazione (la prima transazione avra' numero pari a 1)
        pr->setTrxno(trxno);
        txTime = simTime();
        send(pr, "lowerLayerOut"); //invio la polling request

        //schedulo timer di trasmissione che mi servira' per vedere se la transazione verra' completata in tempo
        //(non scadra' mai, perche' verra' cancellato prima dalla coda degli eventi, se il destinatario ha dati da trasmettere e lo fa in tempo)
        scheduleAt(simTime()+par("trxTimer"), trxTimer);
    }
}

//funzione che effettua la comparazione tra due PollingRequest per stabilire l'ordinamento relativo nella coda delle PollingRequest
//dato che viene passata come funzione di comparazione nel costruttore della coda, essa determina l'ordinamento complessivo della stessa
//questa funzione di fatto implementa la politica di scheduling del master, che coincide proprio con il metodo di ordinamento della coda.
int PollingMaster::poll_queue_comp(cObject *a, cObject *b) {
    PollingRequest *ta = check_and_cast<PollingRequest *>(a);
    PollingRequest *tb = check_and_cast<PollingRequest *>(b);

    //se ta ha priorità maggiore di tb, ritorna un numero < 0
    //(come vogliamo: + basso il valore, + alta la priorità => ta viene prima di tb, e' piu' prioritario)
    return (tb->getPriority()-ta->getPriority());
}
