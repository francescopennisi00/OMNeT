#include "PollingLayer.h"
#include "PollingPackets_m.h"
#include "ApplicationPackets_m.h"

Define_Module(PollingLayer);

void PollingLayer::initialize() {
    burstSize = par("burstSize");
    sigQueueLen = registerSignal("PollingQueueSize");
}

void PollingLayer::handleMessage(cMessage *msg) {
    if(msg->getArrivalGate() == gate("upperLayerIn")) {
        cPacket *pkt = check_and_cast<cPacket *>(msg);
        PollingData *pdata = new PollingData("PollingDataPacket");
        pdata->setByteLength(6);
        DataControlInfo *ci = dynamic_cast<DataControlInfo *>(pkt->removeControlInfo());
        pdata->encapsulate(pkt);
        pdata->setDestination(ci->getDestination());
        ci->setDestination(par("controllerAddress").stringValue());
        pdata->setControlInfo(ci);

        appTxQueue.insert(pdata);
        emit(sigQueueLen, appTxQueue.getLength());
        return;
    }

    /* Pacchetto arrivato da lowerLayerIn */
    PollingRequest *req = dynamic_cast<PollingRequest *>(msg);
    if(req != nullptr) {
        int numframe = burstSize;

        if(strcmp(par("flow").stringValue(), req->getFlow()) != 0) {
            delete req;
            return;
        }

        if(req->getRequestedFrames() > 0) numframe = req->getRequestedFrames();

        for(int i=0; i<numframe && (!appTxQueue.isEmpty()); i++) {
            PollingData *pkt = check_and_cast<PollingData *>(appTxQueue.pop());
            pkt->setTrxno(req->getTrxno());
            pkt->setKind(i);  //aggiunto per scopi di debug
            if(i == (numframe-1)) pkt->setLast(true);
            emit(sigQueueLen, appTxQueue.getLength());
            send(pkt, "lowerLayerOut");
            EV_DEBUG << getFullPath() << " -- Inviata polling data all'interfaccia Ethernet" << endl;
        }

        delete req;
        return;
    }

    send(msg, "upperLayerOut");
}
