#ifndef __SIMPLEETHERNET_ETHERNETPHY_H_
#define __SIMPLEETHERNET_ETHERNETPHY_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class EthernetPhy : public cSimpleModule
{
  protected:
    typedef enum {
        TX_IDLE_STATE,
        TX_TX_STATE,
        TX_IFG_STATE
    } tx_state_t;


    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual void checkAndTransmit();

  protected:
    double datarate;
    tx_state_t txState;
    cPacketQueue txQueue;
    cGate *upperLayerIn;
    simsignal_t sigQueueLen;

};

#endif
