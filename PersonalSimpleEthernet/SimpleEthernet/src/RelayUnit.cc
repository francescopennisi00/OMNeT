#include "RelayUnit.h"

Define_Module(RelayUnit);

void RelayUnit::initialize()
{
    //settaggio delle entries statiche nella tabella di forwarding della RelayUnit dello switch (passate come parametro nel file .ini)
    StaticRelayEntries* te = check_and_cast<StaticRelayEntries*>(par("staticEntries").objectValue()); //objectValue torna un cObject*
    for(int i = 0; i < te->getEntriesArraySize(); i++) {
        RelayTableEntry rte = te->getEntries(i);

        //costruiamo una entry generica della tabella di forwarding che conterra' l'indirizzo e porta della entry statica passata
        //come parametro piu' gli altri due campi che sono settati da noi ( staticEntry = true e updateTime = simTime() )
        table_entry_t *te = new table_entry_t;

        //nel file .msg addr e' una omnetpp:opp_string (perche' definita come pura 'string') => la convertiamo in std::string con str()
        te->addr = rte.addr.str();

        te->port = rte.port;
        te->staticEntry = true;
        te->updateTime = simTime();
        relayTable.push_back(te);
    }
}

void RelayUnit::handleMessage(cMessage *msg)
{
   int idx = msg->getArrivalGate()->getIndex(); //in idx mettiamo la porta (indice del vettore delle porte) da cui arriva il messaggio

   EthernetFrame *frame = check_and_cast<EthernetFrame *>(msg);

   //mi prendo la porta dello switch da cui arriva il frame e la sua sorgente e le uso per aggiornare la tabella di forwarding
   updateTableEntry(idx, frame->getSrc());

   //voglio sapere se nella tabella c'e' una entry che mi sa dire a quale gate devo passare il frame in base alla sua destinazione
   int didx = getPortFromAddr(frame->getDst());

   //non abbiamo trovato la porta, mandiamo il frame in broadcast
   if (didx < 0) {
       for(int i = 0; i < gateSize("lowerLayerOut"); i++) {
           //non ha senso reinviare il frame al nodo da cui e' arrivato
           if (i != idx) {
              //essendo che dobbiamo inviare lo stesso frame a piu' destinazioni (broadcast), lo dobbiamo duplicare
              send(frame->dup(), "lowerLayerOut", i);
           }
       }
       //abbiamo duplicato il frame, quello originale non ci serve più
       delete frame;
       return;
   }

   //abbiamo trovato la porta di destinazione, quindi lo inviamo li'
   send(frame,"lowerLayerOut", didx);

}

//ritorna la porta dello switch su cui inoltrare un frame in base all'indirizzo di destinazione del frame consultando la tabella
int RelayUnit::getPortFromAddr(const char* addr) {
    for(int i=0; i <relayTable.size(); i++) {
        if (strcmp(addr,relayTable[i]->addr.c_str()) == 0) { //la entry i-esima associa l'indirizzo a una porta dello switch
            return relayTable[i]->port;  //la porta port e' un'index del vettore delle porte (!= i, che e' l'indice della entry)
        }
    }
    return -1; //la porta cercata non c'e' (non c'e' la corrispondenza indirizzo-porta, cioe' la entry nella tabella cercata)
}

//aggiorna la tabella di forwarding in base alla porta da cui arriva il messaggio e al suo indirizzo di sorgente
// => la prossima volta che ci sara' un nuovo frame da inoltrare con destinazione uguale alla sorgente del frame corrente (addr),
//    la porta a cui dovro' mandarlo e' quella da cui e' appena arrivato il frame corrente (port)
void RelayUnit::updateTableEntry(int port, const char* addr) {
    int p = getPortFromAddr(addr);
    if (p < 0) { //se non abbiamo trovato l'entry, la dobbiamo aggiungere
        table_entry_t *entry = new table_entry_t;
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
            if(!relayTable[i]->staticEntry) {
                //aggiorno la porta associata all'indirizzo addr (sorgente del frame corrente al momento della chiamata della funzione)
                relayTable[i]->port = port;
                relayTable[i]->updateTime = simTime(); //aggiorno l'istante di update della entry pre-esistente
            }
        }
    }
}
