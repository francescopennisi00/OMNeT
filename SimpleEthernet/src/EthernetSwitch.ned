package simpleethernet;

module EthernetSwitch
{
    parameters:
        @display("bgb=719,483;i=device/hub");
        int portCount = default(4);

    gates:
        input channelIn[portCount];
        output channelOut[portCount];

    submodules:
        port[portCount]: EthernetPhy {
            @display("p=327,373");
        }
        relay: RelayUnit {
            @display("p=325,140");
            relayPortCount = parent.portCount;
        }
    connections:
        for i=0..portCount-1 {
            port[i].channelIn <-- channelIn[i];
            port[i].channelOut --> channelOut[i];
            port[i].upperLayerOut --> relay.lowerLayerIn[i];
            port[i].upperLayerIn <-- relay.lowerLayerOut[i];
        }
}
