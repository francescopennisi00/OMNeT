#ifndef __SIMPLEETHERNET_ETHERNETDATALINK_H_
#define __SIMPLEETHERNET_ETHERNETDATALINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class EthernetDataLink : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  protected:
    cGate* upperLayerIn;
    cGate* lowerLayerIn;
    std::string srcName;
};

#endif
