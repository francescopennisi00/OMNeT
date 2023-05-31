#ifndef __SIMPLEETHERNET_POLLINGMASTER_H_
#define __SIMPLEETHERNET_POLLINGMASTER_H_

#include <omnetpp.h>
#include "PollingPacket_m.h"

using namespace omnetpp;

class PollingMaster : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    //controlla che il canale sia libero e nel caso trasmette una Polling Request per il nodo successivo previsto dalla schedulazione
    virtual void sendNextPollRequest();

    //funzione che determina la priorita' nell'ordinamento della coda di schedulazione delle polling request:
    //cObject è la classe da cui derivano tutte le altre ma nell'implementazione i nostri argomenti saranno delle PollingRequest, proprio
    //perche' vogliamo stabilire la priorita' attraverso delle comparazioni tra PollingRequest (ci baseremo sul loro campo priority)
    static int poll_queue_comp(cObject *a, cObject *b);

  protected:

    //dobbiamo creare una coda di PollingRequest (e' con questa che si attua la schedulazione dei flussi perche' l'ordine di estrazione
    //delle Polling Request determina la schedulazione dei flussi applicativi)
    cPacketQueue pollQueue; //dichiarata staticamente perche' non deve essere modificata ed e' solo del modulo

    //puntatore ad un oggetto della classe tabella di flussi
    FlowTableParameters *flowTable;

    //se true, il canale e' occupato, nel senso che il modulo PollingMaster ha trasmesso verso il nodo schedulato una PollingRequest
    //e attende da esso un PollingData; false altrimenti
    bool onGoingTransaction;

    cMessage* trxTimer;  //timer di transazione

    uint64_t trxno;  //numero di transazione di PollingRequest-PollingData (serve a distinguere le varie richieste di polling ai vari nodi della rete)

    simtime_t txTime; //tempo di trasmissione di una PollingRequest

    simsignal_t sigTrxTime;//segnale per il tempo di transazione (intervallo da quando inviamo la PollingRequest a quando riceviamo il PollingData associato)
};

#endif
