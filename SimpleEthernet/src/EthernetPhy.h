#ifndef __SIMPLEETHERNET_ETHERNETPHY_H_
#define __SIMPLEETHERNET_ETHERNETPHY_H_

#include <omnetpp.h>

using namespace omnetpp;

class EthernetPhy : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void checkAndTransmit();

  protected:
    typedef enum {
        TX_IDLE_STATE,
        TX_TX_STATE,
        TX_IFG_STATE
    } tx_state_t;

  protected:
    double datarate;
    tx_state_t txState;
    cPacketQueue txQueue; //coda di trasmissione dichiarata staticamente perche' non deve essere modificata ed è solo del modulo
    cGate *upperLayerIn;

};

#endif
