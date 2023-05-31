#include "EthernetDataLink.h"
#include "ApplicationPacket_m.h"
#include "EthernetFrame_m.h"

Define_Module(EthernetDataLink);

void EthernetDataLink::initialize()
{
    upperLayerIn = gate("upperLayerIn");
    lowerLayerIn = gate("lowerLayerIn");

//mettiamo in srcName (string che contiene l'indirizzo sorgente dei frame che verrano trasmessi e che ingloberanno il pacchetto dall'
//alto) la string del full path dell'interfaccia Ethernet che racchiude il livello di collegamento corrente (questo simple module)

    srcName = getParentModule()->getFullPath(); //e' l'interfaccia Ethernet la sorgente dei frame
    EV_DEBUG << "SRC Address: " << srcName << endl;
}

void EthernetDataLink::handleMessage(cMessage *msg)
{
    //confronto tra puntatori (il pacchetto arriva dal nodo)
    if(msg->getArrivalGate() == upperLayerIn) {
        cPacket* pkt = check_and_cast<cPacket*>(msg); //prima era un DataPacket, ora un cPacket perche' potrebbe essere una PollingRequest o una PollingData
        //estraiamo le informazioni di controllo associate al dato utile
        DataControlInfo* ci = dynamic_cast<DataControlInfo*>(msg->removeControlInfo());
        if(ci == nullptr) {
            error("Mancano le control info"); //con error si stoppa la simulazione
        }
        //creiamo una frame Ethernet costruita con le control info dall'applicazione
        EthernetFrame *frame = new EthernetFrame("Ethernet Frame");
        frame->setDst(ci->getDestination());
        //il modulo sorgente di un pacchetto e' l'interfaccia Ethernet (livelli collegamento + fisico)
        //poiche' il modulo corrente è il data link, prendiamo il full path del genitore come sorgente
        //EV <<" full path: " <<srcName <<endl;
        frame->setSrc(srcName.c_str());

        if(pkt->getByteLength() < 46) {  //in tal caso dovremmo aggiungere il padding al payload applicativo per raggiungere la dimensione minima di 46 byte
            int padd = 46 - pkt->getByteLength();
            padd += frame->getByteLength();
            frame->setByteLength(padd);
        }

        //incapsuliamo il DataPacket o la PollingRequest o la PollingData, cioè il payload applicativo (senza control info, rimosse), nel frame
        frame->encapsulate(pkt);

        //inviamo il frame al livello fisico
        send(frame,"lowerLayerOut");
        delete ci; //ormai le control info sono inutili e vanno eliminate
        return;
    }

    //il frame arriva dalla rete: se destinato a noi (alla nostra Ethernet Interface), lo decapsuliamo e inviamo il pachetto al dispatcher

    EthernetFrame* et = check_and_cast<EthernetFrame*>(msg);

    if((strcmp(et->getDst(),srcName.c_str()) != 0 ) && strcmp(et->getDst(),"broadcast") != 0) {
        delete et;
        return;
    }

    //il frame che arriva dalla rete e' destinato a noi (alla nostra Ethernet Interface)

    EV_DEBUG <<"Ricevuta frame da: " <<et->getSrc() << "di dimensione: " << et->getByteLength() << " bytes " <<endl;

    //decapsuliamo il frame ed otteniamo il pacchetto ed eliminiamo il frame (ormai inutile)
    cPacket* rxpkt = et->decapsulate();
    delete et;
    send(rxpkt,"upperLayerOut");

}
