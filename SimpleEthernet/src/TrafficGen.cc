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
    signalBurstE2eDelay = registerSignal("BurstEtoEDelay");;
    signalThroughput = registerSignal("SigThroughput");;

    totBit=0;

}

void TrafficGen::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        //potremmo avere piu timer, li distinguiamo dal nome
        if(strcmp(msg->getName(),"TxTimer") == 0 ) {
            generate(); //generazione e trasmissione del burst
            //dobbiamo rischedulare il timer per la trasmissione successiva
            scheduleAt(simTime()+ par("period"), msg); //simTime() ritorna il tempo corrente di simulazione
            return;
        }
    }

    //il messaggio arriva dal gate

    //check_and_cast fa il cast se si puo', senno' genera errore, mentre dynamic_cast torna null
    DataPacket *pkt = check_and_cast< DataPacket *>(msg);

    if(strcmp(pkt->getName(), par("flow").stringValue()) != 0) {
        //il pacchetto non è corretto
        delete pkt;
        return;
    }

    //il messaggio arrivato dal gate è corretto => emettiamo i segnali per le statistiche

    simtime_t delay = simTime()-pkt->getGenTime();
    emit(signalE2eDelay,delay);  //emettiamo il segnale per il delay end-to-end del pacchetto

    totBit += pkt->getBitLength();
    double thr = (double)totBit/(simTime().dbl());
    emit(signalThroughput,thr); //emettiamo il segnale per il throughput

    //solo per l'ultimo pacchetto possiamo emettere il segnale del delay end-to-end dell'intero burst
    if(pkt->getLastBurstPacket()) {
        delay = simTime()- pkt->getGenTime();
        emit(signalBurstE2eDelay,delay); //emettiamo il segnale per il delay end-to-end del burst
    }

    //eliminiamo il messaggio perché non serve più
    delete pkt;
}

//generazione e trasmissione di un burst di messaggi
void TrafficGen::generate(){

    //dobbiamo definire sia il messaggio utile che un messaggio applicativo che contenga quello utile
    DataPacket *pkt;
    DataControlInfo *ci;
    int i;
    int burst = par ("burstSize");
    for(i=0;i<burst;i++) {
        pkt = new DataPacket(par("flow").stringValue());
        pkt->setGenTime(simTime());
        if( i == (burst-1)) {
            pkt->setLastBurstPacket(true);
        }
        pkt->setByteLength(par("payloadLength"));

        ci = new DataControlInfo();
        ci->setDestination(par("destination").stringValue());

        //dobbiamo agganciare le informazioni di controllo al pacchetto: usiamo la funzione nativa di
        //packet setControlInfo() a cui passiamo come parametro il puntatore all'oggetto DataControlInfo
        pkt->setControlInfo(ci);
        send(pkt,"lowerLayerOut"); //inviamo il messaggio
    }
}
