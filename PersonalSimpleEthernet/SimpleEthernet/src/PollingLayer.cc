#include "PollingLayer.h"
#include "ApplicationPacket_m.h"
#include "PollingPacket_m.h"

Define_Module(PollingLayer);

void PollingLayer::initialize()
{
    burstSize = par("burstSize");
    sigQueueLen = registerSignal("PollingQueueSize");
}

void PollingLayer::handleMessage(cMessage *msg)
{
    //se arriva un messaggio da sopra (dall'applicazione collegata al PollingLayer) lo mettiamo in coda di trasmissione
    if(msg->getArrivalGate() == gate("upperLayerIn")) {

        //il pacchetto viene immesso in un PollingData, che verra' inviata al master quando al modulo sopraggiungera' dal Master una PollingRequest
        //quindi, il pacchetto verra', entro un PollingData, deviato verso il controller (polling master):
        //sara' lui a inviarlo alla destinazione dopo averlo schedulato

        cPacket *pkt = check_and_cast<cPacket*>(msg);
        PollingData *pdata = new PollingData("PollingDataPacket"); //costruisco il messaggio che serve al polling master

        //probabilmente da togliere, ma il prof l'ha lasciata, per ora
        pdata->setByteLength(6); //e' a 6 byte perché contiene l'indirizzo di destinazione del pacchetto

        //estraggo le control info, che servono per recuperare l'indirizzo di destinazione del pacchetto, da immettere nel campo
        //apposito del messaggio che serve al polling master (PollingData *pdata)

        DataControlInfo *ci = dynamic_cast<DataControlInfo*>(pkt->removeControlInfo());
        /*
        if(ci == nullptr) {
            error("POLLING LAYER: Mancano le control info"); //con error si stoppa la simulazione
        }
        */
        pdata->encapsulate(pkt); //incapsulo il pacchetto applicativo nel polling message per il master polling

        //inserisco nel campo destination del polling message per il polling master la destinazione del pacchetto applicativo
        pdata->setDestination(ci->getDestination());

        //riuso le control info, cambiando destination address con l'indirizzo del controller master polling
        ci->setDestination(par("controllerAddress").stringValue());

        //mettiamo le control info (quindi associamo l'indirizzo di destinazione: cioe' quello del controller) nel pacchetto PollingData,
        //che incapsula il pacchetto applicativo e la destinazione di quest'ultimo, che sara'l'interfaccia Ethernet di un altro host
        //NB. il pacchetto applicativo contiene al suo interno il nome del flusso, quindi tale pacchetto, una volta giunto all'host
        //di destinazione, arrivera' in seguito all'applicazione di destinazione
        pdata->setControlInfo(ci);

        appTxQueue.insert(pdata); //inserimento del pacchetto pdata con dentro il pacchetto applicativo in coda di trasmissione
        emit(sigQueueLen, appTxQueue.getLength()); //emissione del segnale della lunghezza della coda di trasmissione
        return;

    }

    /* Pacchetto arrivato da lowerLayerIn, cioe' dal dispatcher*/

    //il pacchetto che ci arriva o e' una polling request (comandata dal polling master) o e' un pacchetto dati
    PollingRequest *req = dynamic_cast<PollingRequest *>(msg);//se non si può fare il cast (il messaggio e' un pacchetto dati) torna null

    if (req != nullptr) {  //il pacchetto e' una polling request

   //HP x ora: il numero di frame da estrarre dalla coda sia pari al burstSize di default (parametro modulo, <= di quello del TrafficGen)
        int numframe = burstSize;
        if (strcmp(par("flow").stringValue(), req->getFlow()) != 0) {
            //se non e' del flusso giusto, dobbiamo scartare il pacchetto (la polling request)
            delete req;
            return;

        }

        //il flusso e' giusto, dunque il messaggio e' una polling request per l'applicazione collegata al polling layer

       //se specificato nella polling request, aggiorniamo il numero di frame da estrarre dalla coda di trasmissione (non piu' burstSize)
        if(req->getRequestedFrames()>0) numframe=req->getRequestedFrames();

        for(int i = 0; i<numframe && (!appTxQueue.isEmpty()); i++) {
            //estrazione di un pacchetto polling data per il master polling con dentro un pacchetto applicativo

            PollingData * pd = check_and_cast<PollingData*>(appTxQueue.pop());
            pd->setTrxno(req->getTrxno());
            if(i==(numframe-1)) {
                pd->setLast(true);
            }
            emit(sigQueueLen,appTxQueue.getLength()); //emetto il segnale per la dimensione della coda



            //mando il pacchetto polling data al dispatcher


            //il dispatcher lo passera' al livello MAC, che, a partire dalle control info estratte, costruira' un frame con destinazione
            //l'interfaccia Ethernet dell'host dove risiede il PollingMaster e lo inviera' al livello fisico, che lo immettera' nel canale

            //arrivato il frame al livello di collegamento dell'host Master, verra' estratto da esso il polling data e diretto verso il dispatcher
            //il dispatcher e' collegato verso l'alto con tutti i polling layer delle applicazioni e anche con il polling master
            //i polling layer passano il polling data verso la relative applicazioni, che lo scartano perche' il nome del
            //polling data e' "PollingDataPacket" e non il nome del flusso che si aspettano,
            //mentre il polling master estrae il pacchetto applicativo e la sua destinazione dal polling data,
            //associa al pacchetto applicativo delle control info che contengano la sua destinazione
            //e lo reinvia al dispatcher, che lo passa all'interfaccia Ethernet per la costruzione di un frame che incapsuli
            //direttamente il pacchetto applicativo e per la sua trasmissione verso l'interfaccia Ethernet dell'host di destinazione

            send(pd, "lowerLayerOut");
        }

        delete req;
        return;
    }

    // il pacchetto non e' una request polling, ma e' un pacchetto dati: lo mando al livello applicativo
    //(sara' l'applicazione a scartarlo se non e' del flusso giusto)
    send(msg, "upperLayerOut");

}
