#ifndef __SIMPLEETHERNET_POLLINGLAYER_H_
#define __SIMPLEETHERNET_POLLINGLAYER_H_

#include <omnetpp.h>

using namespace omnetpp;

class PollingLayer : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  protected:
    cPacketQueue appTxQueue;
    int burstSize;
    simsignal_t sigQueueLen;
};

#endif
