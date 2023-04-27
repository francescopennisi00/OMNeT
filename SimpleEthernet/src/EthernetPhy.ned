package simpleethernet;

simple EthernetPhy
{
    parameters:
        double datarate @unit(bps) = default(1Gbps);
        @display("i=block/mac");
    gates:
        output upperLayerOut;
        input upperLayerIn;
        output channelOut;
        input channelIn;
}
