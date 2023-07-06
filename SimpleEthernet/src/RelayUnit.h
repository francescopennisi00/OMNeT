#ifndef __SIMPLEETHERNET_RELAYUNIT_H_
#define __SIMPLEETHERNET_RELAYUNIT_H_

#include <omnetpp.h>
#include "EthernetFrames_m.h"

using namespace omnetpp;

class RelayUnit : public cSimpleModule {
  protected:

    typedef struct {
        std::string addr;
        int port;
        simtime_t updateTime;
        bool staticEntry;
    } table_entry_t;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual int getPortFromAddr(const char *addr);
    virtual void updateTableEntry(int port, const char *addr);

    std::vector<table_entry_t *> relayTable;
};

#endif
