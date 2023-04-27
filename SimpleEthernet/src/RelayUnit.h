#ifndef __SIMPLEETHERNET_RELAYUNIT_H_
#define __SIMPLEETHERNET_RELAYUNIT_H_

#include <omnetpp.h>

using namespace omnetpp;

class RelayUnit : public cSimpleModule
{
  protected:

    //definiamo la riga di una tabella di forwarding
    typedef struct {
        std::string addr;
        int port;
        simtime_t updateTime; //serve a far si' che una entry nella tabella dello switch non sia mai resa statica (se la entry no si aggiorna dopo un tot, la entry viene eliminata)
        bool staticEntry; //per inserire delle entry statiche (parametri di configurazione, non calcolate da sole con il plug and play): se true, abbiamo inserito la entry noi come parametro di configurazione
    } table_entry_t;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual int getPortFromAddr(const char* addr);
    virtual void updateTableEntry(int port, const char* addr);

    //la tabella sarà una lista di table entry (puntatori, in realtà, alle righe della tabella)
    std::vector<table_entry_t*> relayTable;
};

#endif
