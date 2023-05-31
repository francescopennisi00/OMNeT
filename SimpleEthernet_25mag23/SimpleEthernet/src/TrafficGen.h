#ifndef __SIMPLEETHERNET_TRAFFICGEN_H_
#define __SIMPLEETHERNET_TRAFFICGEN_H_

#include <omnetpp.h>

using namespace omnetpp;

class TrafficGen : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual void generate();

    cMessage *txTimer;
    simsignal_t sigE2eDelay;
    simsignal_t sigBurstE2eDelay;
    simsignal_t sigThroughput;
    simsignal_t sigFLR;

    uint64_t totBit;
    uint64_t TxSeqno;
    uint64_t RxSeqno;
    uint64_t rxLost;
    uint64_t rxTot;
};

#endif
