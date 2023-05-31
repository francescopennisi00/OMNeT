#include "EthernetDatalink.h"
#include "EthernetFrames_m.h"
#include "ApplicationPackets_m.h"

Define_Module(EthernetDatalink);

void EthernetDatalink::initialize()
{
    lowerLayerIn = gate("lowerLayerIn");
    upperLayerIn = gate("upperLayerIn");

    srcName = getParentModule()->getFullPath();
    EV_DEBUG << "SRC Address: " << srcName << endl;
}

void EthernetDatalink::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate() == upperLayerIn) {
        cPacket *pkt = check_and_cast<cPacket*>(msg);
        DataControlInfo *ci = dynamic_cast<DataControlInfo*>(msg->removeControlInfo());
        if(ci == nullptr) {
            error("Mancano le control info");
        }
        EthernetFrame *frame = new EthernetFrame("EthernetFrame");
        frame->setDst(ci->getDestination());
        frame->setSrc(srcName.c_str());
        if(pkt->getByteLength() < 46) {
            int pad = 46-pkt->getByteLength();
            pad += frame->getByteLength();
            frame->setByteLength(pad);
        }
        frame->encapsulate(pkt);
        send(frame, "lowerLayerOut");
        delete ci;
        return;
    }

    EthernetFrame *et = check_and_cast<EthernetFrame*>(msg);
    if(strcmp(et->getDst(), srcName.c_str()) != 0 && strcmp(et->getDst(), "broadcast") != 0) {
        delete et;
        return;
    }

    EV_DEBUG << "Ricevuta frame da: " << et->getSrc() << " di dim: "
            << et->getByteLength() << " bytes" << endl;
    cPacket *rxpkt = et->decapsulate();
    delete et;
    send(rxpkt, "upperLayerOut");
}
