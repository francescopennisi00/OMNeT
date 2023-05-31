#include "EthernetPhy.h"
#include "EthernetFrame_m.h"

Define_Module(EthernetPhy);

void EthernetPhy::initialize()
{
    datarate = par("datarate");
    txState = TX_IDLE_STATE;
    upperLayerIn = gate("upperLayerIn");  //puntatore alla porta da cui arrivano i frame da trasmettere (porta con il DataLink)
    sigQueueLen = registerSignal("QueueSize");
}

void EthernetPhy::handleMessage(cMessage *msg)
{
    EthernetFrame* frame;

    //controllo se il messaggio ricevuto e' frutto di un timer (in particolare, della sua scadenza):
    // ES. scandenza del timer che conta l'intervallo di tempo in cui siamo nello stato di trasmissione o in cui siamo in IFG)
    if(msg->isSelfMessage()) {

        //il timer e' di trasmissione (il messaggio di timer contiene anche il frame da trasmettere)
        //alla scadenza di questo timer noi immettiamo il frame nel canale ma questo è per simulare
        //che abbiamo appena finito di inviare il frame stesso e dobbiamo passare a IFG_STATE
        if(strcmp(msg->getName(),"TxTimer") == 0) {
            frame = check_and_cast<EthernetFrame*>(msg->removeControlInfo());//estraggo il frame (= control info del messaggio TxTimer)
            delete msg; //abbiamo il frame, msg (cioè il timer che la ingloba) non ci serve piu'
            send(frame,"channelOut"); //immettiamo il frame da trasmettere nel canale

            //dobbiamo far partire il timer di InterFrameGap (periodo tra due trasmissioni di un frame consecutive)
            cMessage* ifgTimer = new cMessage("IFGTimer");
            scheduleAt(simTime()+SimTime(96.0/datarate),ifgTimer);  //IFG dura un tempo di 12 byte = 96 bit
            txState = TX_IFG_STATE;
            return;

        //il timer e' quello di interframe gap (è appena scaduto e quindi bisogna andare o in IDLE o in TX)
        } else if (strcmp(msg->getName(),"IFGTimer") == 0) {
            delete msg; //questo messaggio e' intrinsecamente inutile perche' non contiene alcun frame

            //se la coda non e' vuota, trasmettiamo un altro frame in un evento timer per la trasmissione,
            //altrimenti andiamo in IDLE
            checkAndTransmit();
            return;
        }
    }

    //l'evento è un frame dall'alto: dal livello MAC (di conseguenza è asincrono rispetto al timer di trasmissione e a quello di IFG)
    //oppure è un frame arrivato dal canale
    frame = check_and_cast<EthernetFrame*>(msg);

    //il frame arriva dal nodo
    if(frame->getArrivalGate() == upperLayerIn) {

        txQueue.insert(frame);  //non importa in che stato di TX ci troviamo, mettiamo in ogni caso il frame in coda

        //abbiamo inserito in coda => emissione del segnale che ci dice quanti frame sono in coda di trasmissione
        emit(sigQueueLen, txQueue.getLength());

        //solo se lo stato è idle, si chiama checkAndTransmit() per una nuova trasmissione sul canale
        if(txState == TX_IDLE_STATE) {
            checkAndTransmit();
            return;
        }
        return;
    }

    //il frame è arrivato dal canale e dunque lo inviamo al livello di collegamento soprastante,
    //indipendentemente da qual è lo stato in trasmissione (lo possiamo fare perche' Ethernet e' full-duplex)

    //prima dell'invio dobbiamo controllare che la frame sia integra, altrimenti la frame va solo eliminata (senza chiedere ritrasmissione)
    if(frame->hasBitError() == false) {
       send(frame,"upperLayerOut");
    } else {
        delete frame;
    }

}

//se la coda non è vuota, associamo un frame a un timer di trasmissione: evento timer = scadenza periodo di durata della trasmissione
void EthernetPhy::checkAndTransmit() {
    if(!(txQueue.isEmpty())) {
        EthernetFrame* frame = check_and_cast<EthernetFrame*>(txQueue.pop());
        emit(sigQueueLen, txQueue.getLength()); //abbiamo estratto dalla coda => emissione del segnale del numero di frame in essa
        cMessage *txTimer = new cMessage("TxTimer");
        double txt = (double)frame->getBitLength()/datarate;  //durata della trasmissione del frame (txt = transmission time)
        EV_DEBUG << "Txt: " << txt << " - Byte: " << frame->getByteLength() <<endl;
        scheduleAt(simTime()+SimTime(txt), txTimer);
        txTimer->setControlInfo(frame);  //il frame estratto dalla coda diventa la control info del messaggio di transmission timer
        txState = TX_TX_STATE;
    } else {
        txState = TX_IDLE_STATE;
    }
}
