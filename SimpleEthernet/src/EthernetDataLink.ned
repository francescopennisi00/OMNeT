package simpleethernet;

//
// livello di collegamento dell'host Ethernet: non ci sono contese ed è full-duplex
//
simple EthernetDataLink
{
    @display("i=block/layer");
    
    //porte solo verso il dispatcher e verso il livello fisico
    gates:
        output upperLayerOut;
        input upperLayerIn;
        output lowerLayerOut;
        input lowerLayerIn;
}
