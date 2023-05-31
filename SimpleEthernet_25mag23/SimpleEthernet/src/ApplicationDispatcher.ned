package simpleethernet;

simple ApplicationDispatcher
{
    @display("i=block/dispatch");
    gates:
        output upperLayerOut[];
        input upperLayerIn[];
        output lowerLayerOut;
        input lowerLayerIn;
}
