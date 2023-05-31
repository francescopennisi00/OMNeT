#include "TrafficGen.h"
#include "ApplicationPacket_m.h"

Define_Module(TrafficGen);

void TrafficGen::initialize()
{
    simtime_t st = par("startTime");
    if(st >= 0) {
        //il nodo e' attivo in trasmissione e dobbiamo schedulare un timer per la prima trasmissione
        txTimer = new cMessage("TxTimer");
        scheduleAt(st, txTimer);
    }

    signalE2eDelay = registerSignal("EtoEDelay");
    signalBurstE2eDelay = registerSignal("BurstEtoEDelay");
    signalThroughput = registerSignal("SigThroughput");
    sigFLR = registerSignal("FLR");

    totBit=0;
    Txseqno = 0;
    Rxseqno = 0;
    rxLost = 0;
    rxTot = 0;

}

void TrafficGen::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        //potremmo avere piu timer, li distinguiamo dal nome
        if(strcmp(msg->getName(),"TxTimer") == 0 ) {
            generate(); //generazione e trasmissione del burst
            //dobbiamo rischedulare il timer per la trasmissione successiva
            scheduleAt(simTime()+par("period"), msg); //simTime() ritorna il tempo corrente di simulazione
            return;
        }
    }

    //il messaggio arriva dal gate

    //check_and_cast fa il cast se si puo', senno' genera errore, mentre dynamic_cast torna null nel caso in cui non sia possibile
    DataPacket *pkt = check_and_cast<DataPacket *>(msg);

    //nome pacchetto = nome flusso a cui appartiene (se il pacchetto ricevuto non e' del flusso del TrafficGen corrente, lo scartiamo)
    if(strcmp(pkt->getName(), par("flow").stringValue()) != 0) {
        //il pacchetto non è corretto
        delete pkt;
        return;
    }

    //capiamo se l'ordine di ricezione dei pacchetti e' rispettato
    //(il primo pacchetto, cioe' quello quando Rxsegno == 0, dovrebbe avere numero di sequenza 1)
    if((Rxseqno+1) < pkt->getSeqno()) {
        //abbiamo perso pacchetti poiche' abbiamo perso frame
        rxLost += (pkt->getSeqno() - Rxseqno);
    } else {  //in caso contrario, sicuro Rxsegno+1 == pkt->getSeqno(), come dovrebbe essere, perche' il > non potrebbe essere mai
        rxTot++;
    }
    //indipendentemente dal fatto che abbiamo o meno perso pacchetti, il numero di sequenza in ricezione diventa quello dell'ultimo pacchetto
    //che e' stato ricevuto, perche' non ci interessa di richiedere ritrasmissioni
    Rxseqno = pkt->getSeqno();

    //emettiamo i segnali per le statistiche aggiornate dalla ricezione del pacchetto

    //FLR = (numero di pacchetti, quindi di frame, persi in ricezione)/(numero di pacchetti, quindi di frame, che erano stati inviati
    //complessivamente all'applicazione), con quest'ultimo che e' dato dalla somma tra il numero totale di pacchetti (frame)
    //persi a ricezione e il numero totale di pacchetti (frame) arrivati correttamente
    emit(sigFLR, (double)rxLost/(double)(rxLost + rxTot));

    simtime_t delay = simTime()-pkt->getGenTime();
    emit(signalE2eDelay,delay);  //emettiamo il segnale per il delay end-to-end del pacchetto

    totBit += pkt->getBitLength();
    double thr = (double)totBit/(simTime().dbl());
    emit(signalThroughput,thr); //emettiamo il segnale per il throughput

    //solo per l'ultimo pacchetto possiamo emettere il segnale del delay end-to-end dell'intero burst
    if(pkt->getLastBurstPacket()) {
//tutti i packet del burst sono inviati allo stesso simTime(): hanno uguale genTime(): uso quello dell'ultimo del burst, non del primo)
        delay = simTime()- pkt->getGenTime();
        emit(signalBurstE2eDelay,delay); //emettiamo il segnale per il delay end-to-end dell'intero burst
    }

    //eliminiamo il messaggio perche' non serve piu'
    delete pkt;
}

//generazione e trasmissione di un burst di messaggi
void TrafficGen::generate(){

    //dobbiamo definire sia il messaggio utile (DataPacket) che un messaggio applicativo che contenga quello utile
    //(che sarebbe il DataPacket + le DataControlInfo)
    DataPacket *pkt;
    DataControlInfo *ci;
    int i;
    int burst = par("burstSize");
    for(i=0;i<burst;i++) {
        pkt = new DataPacket(par("flow").stringValue());  //come nome del pacchetto diamo quello del flusso
        pkt->setGenTime(simTime());  //tutti i pacchetti avranno lo stesso generation time
        if(i == (burst-1)) {
            pkt->setLastBurstPacket(true);
        }
        pkt->setByteLength(par("payloadLength"));
        Txseqno++;  //il primo pacchetto avra' numero di sequenza 1
        pkt->setSeqno(Txseqno);

        ci = new DataControlInfo();
        ci->setDestination(par("destination").stringValue());

        //dobbiamo agganciare le informazioni di controllo al pacchetto: usiamo la funzione nativa di
        //packet setControlInfo() a cui passiamo come parametro il puntatore all'oggetto DataControlInfo
        pkt->setControlInfo(ci);
        send(pkt,"lowerLayerOut"); //inviamo il messaggio
    }
}
