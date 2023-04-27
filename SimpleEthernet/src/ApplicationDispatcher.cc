#include "ApplicationDispatcher.h"

Define_Module(ApplicationDispatcher);

void ApplicationDispatcher::initialize()
{

}

void ApplicationDispatcher::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getArrivalGate()->getBaseName(), "upperLayerIn") == 0) {
        send(msg,"lowerLayerOut");
    } else {
        for(int i=0; i<gateSize("upperLayerOut");i++) {
            //poiché va inviato a tutte le applicazioni (ognuna un modulo) il messaggio va duplicato
            send(msg->dup(),"upperLayerOut",i);
        }
        //visto che abbiamo usato i duplicati, la copia del messaggio e' diventata inutile
        delete msg;
    }
}
