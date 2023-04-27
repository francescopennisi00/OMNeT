package simpleethernet;

//
// si occupa di ricevere i dati dal livello MAC e di passarli alle applicazioni e viceversa
//
simple ApplicationDispatcher
{
    @display("i=block/dispatch");
    gates:
        output upperLayerOut[];
        input upperLayerIn[];
        output lowerLayerOut;
        input lowerLayerIn;
}
