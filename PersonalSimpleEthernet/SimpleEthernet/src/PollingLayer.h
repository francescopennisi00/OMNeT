#ifndef __SIMPLEETHERNET_POLLINGLAYER_H_
#define __SIMPLEETHERNET_POLLINGLAYER_H_

#include <omnetpp.h>

using namespace omnetpp;

class PollingLayer : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  protected:
    //coda FIFO di trasmissione dei pacchetti applicativi
    cPacketQueue appTxQueue; //dichiarata staticamente perche' non deve essere modificata ed e' solo del modulo
    int burstSize;
    simsignal_t sigQueueLen; //segnale per la dimensione della coda di trasmissione = numero di elementi in coda di trasmissione
};

#endif
