package simpleethernet;

simple EthernetPhy
{
    parameters:
        double datarate @unit(bps) = default(1Gbps);
        @display("i=block/mac");
        
        @signal[QueueSize];
        @statistic[QueueSize](record=vector,max);
    gates:
        input upperLayerIn;
        output upperLayerOut;
        input channelIn;
        output channelOut;
}
