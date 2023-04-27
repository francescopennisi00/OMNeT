#include "EthernetPhy.h"
#include "EthernetFrame_m.h"

Define_Module(EthernetPhy);

void EthernetPhy::initialize()
{
    datarate = par("datarate");
    txState = TX_IDLE_STATE;
    upperLayerIn = gate("upperLayerIn");
}

void EthernetPhy::handleMessage(cMessage *msg)
{
    EthernetFrame* frame;

    //controllo se il messaggio ricevuto e' frutto di un timer (in particolare, della sua scadenza)
    if(msg->isSelfMessage()) {

        //il timer e' di trasmissione (il messaggio di timer contiene anche il frame da trasmettere)
        //alla scadenza di questo timer noi immettiamo il frame nel canale ma questo è per simulare
        //che abbiamo appena finito di inviare il frame stesso e dobbiamo passare a IFG_STATE
        if(strcmp(msg->getName(),"TxTimer") == 0) {
            frame = check_and_cast<EthernetFrame*>(msg->removeControlInfo()); //estraggo la frame
            delete msg; //abbiamo frame, msg non ci serve piu'
            send(frame,"channelOut"); //immettiamo il frame da trasmettere nel canale

            //dobbiamo far partire il timer di InterFrameGap (dura un tempo di 12 byte = 96 bit)
            cMessage* ifgTimer = new cMessage("IFGTimer");
            scheduleAt(simTime()+SimTime(96.0/datarate),ifgTimer);
            txState = TX_IFG_STATE;
            return;

        //il timer e' quello di interframe gap (è appena scaduto e quindi bisogna andare o in IDLE o in TX)
        } else if (strcmp(msg->getName(),"IFGTimer") == 0) {
            delete msg; //questo messaggio e' intrinsecamente inutile perche' non contiene alcun frame

            //se la coda non e' piena, trasmettiamo un altro frame in un evento timer per la trasmissione,
            //altrimenti andiamo in IDLE
            checkAndTransmit();
            return;
        }
    }

    //l'evento è un frame dall'alto (di conseguenza è asincrono rispetto al timer di trasmissione)
    //oppure è arrivato dal canale
    frame = check_and_cast<EthernetFrame*>(msg);

    //il frame arriva dal nodo
    if(frame->getArrivalGate() == upperLayerIn) {
        txQueue.insert(frame);
        //solo se lo stato è idle, si chiama checkAndTransmit() per una nuova trasmissione sul canale
        if(txState == TX_IDLE_STATE) {
            checkAndTransmit();
            return;
        }
        return;
    }

    //il frame è arrivato dal canale e dunque lo inviamo al livello di collegamento soprastante
    send(frame,"upperLayerOut");

}

//se la coda non è vuota, associamo un frame a un timer di trasmissione che scheduliamo in base alla bitrate
void EthernetPhy::checkAndTransmit() {
    if(!(txQueue.isEmpty())) {
        EthernetFrame* frame = check_and_cast<EthernetFrame*>(txQueue.pop());
        cMessage *txTimer = new cMessage("TxTimer");
        double txt = (double)frame->getBitLength()/datarate;
        scheduleAt(simTime()+SimTime(txt),txTimer);
        txTimer->setControlInfo(frame);  //il frame diventa la control info del timer
        txState = TX_TX_STATE;
        return;
    } else {
        txState = TX_IDLE_STATE;
        return;
    }
}
