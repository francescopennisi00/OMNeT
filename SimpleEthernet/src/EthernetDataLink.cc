#include "EthernetDataLink.h"
#include "ApplicationPacket_m.h"
#include "EthernetFrame_m.h"

Define_Module(EthernetDataLink);

void EthernetDataLink::initialize()
{
    upperLayerIn = gate("upperLayerIn");
    lowerLayerIn = gate("lowerLayerIn");
    srcName = getParentModule()->getFullPath();

}

void EthernetDataLink::handleMessage(cMessage *msg)
{
    //confronto tra puntatori (il pacchetto arriva dal nodo)
    if(msg->getArrivalGate() == upperLayerIn) {
        DataPacket* pkt = check_and_cast<DataPacket*>(msg);
        //estraiamo le informazioni di controllo provenienti dall'applicazione e associate al dato utile
        DataControlInfo* ci = dynamic_cast<DataControlInfo*>(msg->removeControlInfo());
        if(ci == nullptr) {
            error("Mancano le control info"); //con error si stoppa la simulazione
        }
        //creiamo una frame Ethernet costruita con le control info dall'applicazione
        EthernetFrame *frame = new EthernetFrame("Ethernet Frame");
        frame->setDst(ci->getDestination());
        //il modulo sorgente di un pacchetto e' l'interfaccia Ethernet (livelli collegamento + fisico)
        //poiche' il modulo corrente è il data link, prendiamo il full path del genitore come sorgente
        EV <<" full path: " <<srcName <<endl;
        frame->setSrc(srcName.c_str());

        //incapsuliamo il DataPacket, cioè il payload applicativo (senza control info, rimosse), nel frame
        frame->encapsulate(pkt);

        //inviamo il frame al livello fisico
        send(frame,"lowerLayerOut");
        delete ci; //ormai le control info sono inutili e vanno eliminate
        return;
    }

    //il frame arriva dalla rete: se destinato a noi, lo decapsuliamo e inviamo il pacchetto al dispatcher

    EthernetFrame* et = check_and_cast<EthernetFrame*>(msg);

    if((strcmp(et->getDst(),srcName.c_str()) != 0 ) && strcmp(et->getDst(),"broadcast") != 0) {
        delete et;
        return;
    }

    //il frame era destinato a noi

    EV <<"Ricevuta frame da: " <<et->getSrc() << "di dimensione: "
            << et->getByteLength() << " bytes " <<endl;

    //decapsuliamo il frame ed otteniamo il pacchetto ed eliminiamo il frame (ormai inutile)
    cPacket* rxpkt = et->decapsulate();
    delete et;

    send(rxpkt,"upperLayerOut");

}
