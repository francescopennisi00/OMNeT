#include "ApplicationDispatcher.h"

Define_Module(ApplicationDispatcher);

void ApplicationDispatcher::initialize()
{

}

void ApplicationDispatcher::handleMessage(cMessage *msg)
{
    //se il messaggio arriva da una applicazione (TrafficGen), lo inviamo all'interfaccia Ethernet
    if(strcmp(msg->getArrivalGate()->getBaseName(), "upperLayerIn") == 0) {
        send(msg,"lowerLayerOut");
    } else {  //il messaggio arriva dall'interfaccia Ethernet
        for(int i=0; i<gateSize("upperLayerOut");i++) {
            //poiché va inviato a tutte le applicazioni (ognuna un modulo TrafficGen) il messaggio va duplicato
            send(msg->dup(),"upperLayerOut", i);
        }
        //visto che abbiamo usato i duplicati, la copia del messaggio e' diventata inutile
        delete msg;
    }
}
