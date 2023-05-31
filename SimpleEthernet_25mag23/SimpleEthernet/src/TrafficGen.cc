#include "TrafficGen.h"
#include "ApplicationPackets_m.h"

Define_Module(TrafficGen);

void TrafficGen::initialize() {
    simtime_t st = par("startTime");
    if(st >= 0) {
        txTimer = new cMessage("TxTimer");
        scheduleAt(st, txTimer);
    }

    sigE2eDelay = registerSignal("E2eDelay");
    sigBurstE2eDelay = registerSignal("BurstE2eDelay");
    sigThroughput  = registerSignal("Throughput");
    sigFLR = registerSignal("FLR");

    totBit = 0;
    TxSeqno = 0;
    RxSeqno = 0;
    rxLost = 0;
    rxTot = 0;
}

void TrafficGen::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {
        if(strcmp(msg->getName(), "TxTimer") == 0) {
            generate();
            scheduleAt(simTime()+par("period"), msg);
            return;
        }
    }

    DataPacket *pkt = check_and_cast<DataPacket *>(msg);

    if(strcmp(pkt->getName(), par("flow").stringValue()) != 0) {
        delete pkt;
        return;
    }

    if((RxSeqno+1) < pkt->getSeqno()) {
        rxLost += (pkt->getSeqno()-(RxSeqno+1));
    } else {
        rxTot++;
    }
    RxSeqno = pkt->getSeqno();

    emit(sigFLR, (double)rxLost/(double)(rxLost+rxTot));

    simtime_t delay = simTime()-pkt->getGenTime();
    emit(sigE2eDelay, delay);

    totBit += pkt->getBitLength();
    double thr = (double)totBit/simTime().dbl();
    emit(sigThroughput, thr);

    if(pkt->getLastBurstPacket()) {
        delay = simTime()-pkt->getGenTime();
        emit(sigBurstE2eDelay, delay);
    }

    delete pkt;
}

void TrafficGen::generate() {
    DataPacket *pkt;
    DataControlInfo *ci;
    int i;
    int burst = par("burstSize");

    for(i=0; i<burst; i++) {
        pkt = new DataPacket(par("flow").stringValue());
        pkt->setGenTime(simTime());
        if(i == (burst-1)) {
            pkt->setLastBurstPacket(true);
        }
        pkt->setByteLength(par("payloadLength"));
        TxSeqno++;
        pkt->setSeqno(TxSeqno);
        ci = new DataControlInfo();
        ci->setName("DataControlInfo");
        ci->setDestination(par("destination").stringValue());

        pkt->setControlInfo(ci);
        send(pkt, "lowerLayerOut");
    }
}













