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

    //enumerazione per elencare i possibili stati della FSM del livello fisico IN TRASMISSIONE
    typedef enum {
        TX_IDLE_STATE,
        TX_TX_STATE,
        TX_IFG_STATE
    } tx_state_t;

  protected:
    double datarate;
    tx_state_t txState;
    //coda di trasmissione che accoglie tutti i frame giunti dall'alto e da trasmettere
    cPacketQueue txQueue; //dichiarata staticamente perche' non deve essere modificata ed E' solo del modulo
    cGate *upperLayerIn;
    simsignal_t sigQueueLen; //segnale per la lunghezza della coda di trasmissione = numero di elementi in coda di trasmissione

};

#endif
