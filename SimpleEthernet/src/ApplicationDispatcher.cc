#include "ApplicationDispatcher.h"

Define_Module(ApplicationDispatcher);

void ApplicationDispatcher::initialize() {

}

void ApplicationDispatcher::handleMessage(cMessage *msg) {
    if(strcmp(msg->getArrivalGate()->getBaseName(), "upperLayerIn")==0) {
        send(msg, "lowerLayerOut");
    } else {
        for(int i=0; i < gateSize("upperLayerOut"); i++) {
            send(msg->dup(), "upperLayerOut", i);
        }
        delete msg;
    }
}
