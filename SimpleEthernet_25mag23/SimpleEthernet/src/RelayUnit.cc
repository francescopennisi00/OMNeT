#include "RelayUnit.h"

Define_Module(RelayUnit);

void RelayUnit::initialize() {
    StaticRelayEntries *te = check_and_cast<StaticRelayEntries *>(par("staticEntries").objectValue());
    for(int i = 0; i < te->getEntriesArraySize(); i++) {
        RelayTableEntry rte = te->getEntries(i);
        table_entry_t *te = new table_entry_t;
        te->addr = rte.addr.str();
        te->port = rte.port;
        te->staticEntry = true;
        te->updateTime = simTime();
        relayTable.push_back(te);
    }
}

void RelayUnit::handleMessage(cMessage *msg) {
    int idx = msg->getArrivalGate()->getIndex();

    EthernetFrame *frame = check_and_cast<EthernetFrame *>(msg);

    updateTableEntry(idx, frame->getSrc());

    int didx = getPortFromAddr(frame->getDst());
    if(didx < 0) {
        for(int i=0; i< gateSize("lowerLayerOut"); i++) {
            if(i != idx) {
                send(frame->dup(), "lowerLayerOut", i);
            }
        }
        delete frame;
        return;
    }

    send(frame, "lowerLayerOut", didx);
}

void RelayUnit::updateTableEntry(int port, const char *addr) {
    int p = getPortFromAddr(addr);

    if(p < 0) {
        table_entry_t *entry = new table_entry_t;
        entry->addr = std::string(addr);
        entry->port = port;
        entry->staticEntry = false;
        entry->updateTime = simTime();
        relayTable.push_back(entry);
        return;
    }

    for(int i=0; i<relayTable.size(); i++) {
        if(strcmp(addr, relayTable[i]->addr.c_str()) == 0) {
            if(!relayTable[i]->staticEntry) {
                relayTable[i]->port = port;
                relayTable[i]->updateTime = simTime();
            }
        }
    }
}

int RelayUnit::getPortFromAddr(const char *addr) {
    for(int i=0; i<relayTable.size(); i++) {
        if(strcmp(addr, relayTable[i]->addr.c_str()) == 0) {
            return relayTable[i]->port;
        }
    }
    return -1;
}
