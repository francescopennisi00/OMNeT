#ifndef __SIMPLEETHERNET_RELAYUNIT_H_
#define __SIMPLEETHERNET_RELAYUNIT_H_

#include <omnetpp.h>

#include "EthernetFrame_m.h"

using namespace omnetpp;

class RelayUnit : public cSimpleModule
{
  protected:

    //struct che definisce una entry della tabella di forwarding
    typedef struct {

        //ad ogni destinazione corrisponde un indice della porta dove dobbiamo inoltrare il frame che e' arrivato
        std::string addr; //indirizzo di destinazione
        int port;  //indice del vettore delle porte (quindi porta su cui inoltrare il frame da trasmettere)

        //serve a far si' che una entry nella tabella non sia mai resa statica, cioe' non cambi nel tempo ma rimanga comunque in tabella
        //infatti se questo campo non si aggiorna dopo un tot, la entry corrispondente viene eliminata
        simtime_t updateTime;

        //per inserire delle entry statiche (parametri di configurazione, cioe' entry non calcolate con il plug and play):
        //se true, abbiamo inserito la entry noi come parametro di configurazione e questa non deve essere aggiornata con il plug and play
        //ne' eliminata tramite l'updateTime
        bool staticEntry;

    } table_entry_t;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual int getPortFromAddr(const char* addr);
    virtual void updateTableEntry(int port, const char* addr);

    //dichiarazione della tabella di forwarding (= vettore di puntatori alle entries (statiche e non) definite dalla struct)
    std::vector<table_entry_t *> relayTable;

};

#endif
