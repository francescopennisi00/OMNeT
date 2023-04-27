#include "RelayUnit.h"

Define_Module(RelayUnit);

void RelayUnit::initialize()
{
    //dobbiamo implementare la tabella di relay contenuta nello switch
    //(ad ogni destinazione corrisponde un indice della porta o da dove e' arrivata o da dove la dobbiamo trasmettere)
    // --> FATTO NEL FILE .h
}

void RelayUnit::handleMessage(cMessage *msg)
{

}

int RelayUnit::getPortFromAddr(const char* addr) {
    for(int i=0; i <relayTable.size(); i++) {
        if (strcmp(addr,relayTable[i]->addr.c_str()) == 0) {
            return relayTable[i]->port;
        }
    }
    return -1; //la porta cercata non c'e' (non c'e' la corrispondenza indirizzo-porta, cioe' la entry nella tabella)
}

void RelayUnit::updateTableEntry(int port, const char* addr) {
    int p = getPortFromAddr(addr);
    if (p < 0) { //se non abbiamo trovato l'entry, la dobbiamo aggiungere
        table_entry_t* entry = new table_entry_t;
        entry->addr = std::string(addr);
        entry->port = port;
        entry->updateTime = simTime();
        entry->staticEntry = false;
        relayTable.push_back(entry);
        return;
    }

    //abbiamo trovato l'entry: dobbiamo aggiornarla, se non statica
    for(int i=0; i <relayTable.size(); i++) {
        if (strcmp(addr,relayTable[i]->addr.c_str()) == 0) {
            if(!relayTable[i].staticEntry)
                relayTable[i]->port = port;
                relayTable[i]->updateTime = SimTime();
            }
        }
    }
}
