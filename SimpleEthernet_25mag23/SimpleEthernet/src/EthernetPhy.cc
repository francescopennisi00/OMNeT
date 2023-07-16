#include "EthernetPhy.h"
#include "EthernetFrames_m.h"

Define_Module(EthernetPhy);

void EthernetPhy::initialize()
{
    datarate = par("datarate");
    txState = TX_IDLE_STATE;
    upperLayerIn = gate("upperLayerIn");
    sigQueueLen = registerSignal("QueueSize");
}

void EthernetPhy::handleMessage(cMessage *msg) {
    EthernetFrame *frame;

    if(msg->isSelfMessage()) {
        /** Timer */
        if(strcmp(msg->getName(), "TxTimer") == 0) {
            frame = check_and_cast<EthernetFrame *>(msg->removeControlInfo());
            delete msg;
            send(frame, "channelOut");
            cMessage *ifgTimer = new cMessage("IFGTimer");
            scheduleAt(simTime()+SimTime(96.0/datarate), ifgTimer);
            txState = TX_IFG_STATE;
            return;
        } else if(strcmp(msg->getName(), "IFGTimer") == 0) {
            delete msg;
            checkAndTransmit();
            return;
        }
    }

    /** Frame arrivata dai livelli superiori */
    frame = check_and_cast<EthernetFrame *>(msg);
    if(frame->getArrivalGate() == upperLayerIn) {
        txQueue.insert(frame);
        emit(sigQueueLen, txQueue.getLength());
        if(txState==TX_IDLE_STATE) {
            checkAndTransmit();
            return;
        }
        return;
    }

    /** Frame arrivata dalla rete */
    double ber = 0.000000000001;
    if (dblrand() < 1.0 - pow(1.0 - ber, (double)frame->getBitLength())) {
        EV_DEBUG << getFullPath() << " - FRAME SCARTATA" <<endl;
        delete frame;
    } else {
        send(frame,"upperLayerOut");
    }

    /*
    if(frame->hasBitError() == false) {
        send(frame, "upperLayerOut");
    } else {
        delete frame;
    }
    */

}

void EthernetPhy::checkAndTransmit() {
    if(!txQueue.isEmpty()) {
        EthernetFrame *frame = check_and_cast<EthernetFrame *>(txQueue.pop());
        emit(sigQueueLen, txQueue.getLength());
        cMessage *txtimer = new cMessage("TxTimer");
        double txt = (double)frame->getBitLength()/datarate;
        EV_DEBUG << getParentModule()->getFullPath() << " -- Txt: " << txt << " - Byte: " << frame->getByteLength() << endl;
        scheduleAt(simTime()+SimTime(txt), txtimer);
        txtimer->setControlInfo(frame);
        txState = TX_TX_STATE;
    } else {
        txState = TX_IDLE_STATE;
    }
}
