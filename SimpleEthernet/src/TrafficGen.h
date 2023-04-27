#ifndef __SIMPLEETHERNET_TRAFFICGEN_H_
#define __SIMPLEETHERNET_TRAFFICGEN_H_

#include <omnetpp.h>

using namespace omnetpp;


class TrafficGen : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    //funzione che appena richiamata genera e trasmette un burst di pacchetti
    virtual void generate();

    //ci serve un timer per dettare il periodo di trasmissione
    cMessage *txTimer;

    //segnali per le statistiche
    simsignal_t signalE2eDelay; //end to end delay pre il singolo burst e frame
    simsignal_t signalBurstE2eDelay;
    simsignal_t signalThroughput;

    //unsigned int a 64 bit
    uint64_t totBit;
};

#endif
