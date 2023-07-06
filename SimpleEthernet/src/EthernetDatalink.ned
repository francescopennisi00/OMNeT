package simpleethernet;

simple EthernetDatalink
{
    @display("i=block/layer");
    gates:
        output lowerLayerOut;
        input lowerLayerIn;
        output upperLayerOut;
        input upperLayerIn;
}
