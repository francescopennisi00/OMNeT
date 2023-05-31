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


    //segnali per le statistiche della singola TrafficGen

    simsignal_t signalE2eDelay; //end to end delay per il singolo frame
    simsignal_t signalBurstE2eDelay;  //end to end delay per il burst
    simsignal_t signalThroughput;   //troughput complessivo (numero bit totali/simTime()) => throghput da quando inizia la simulazione
    simsignal_t sigFLR;

    //unsigned int a 64 bit per accogliere il numero totale di bit generati dalla TrafficGen
    uint64_t totBit;

    uint64_t Txseqno;  //numero di sequenza di trasmissione
    uint64_t Rxseqno;  //numero di sequenza di ricezione
    uint64_t rxLost;  //numero totale di pacchetti persi in ricezione (non chiediamo per essi la ritrasmissione)
    uint64_t rxTot;   //numero totale di pacchetti arrivati correttamente a destinazione


};

#endif
