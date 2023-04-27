package simpleethernet;

module EthernetSwitch
{
    parameters:
        @display("bgb=794,406;i=device/drive");
        int portCount = default(4); //4 porte dello switch: 4 simple module EthernetPhy contenute nel modulo

    gates:
        input channelIn[portCount];
        output channelOut[portCount];

    submodules:
        port[portCount]: EthernetPhy {
            @display("p=148,220");
        }

        relay: RelayUnit {
            @display("p=501,208");
            //setto i parametri della precisa istanza del RelayUnit
            relayPortCount = portCount;
        }
    connections:
        for i=0..portCount - 1 {
            port[i].channelIn <-- channelIn[i];
            port[i].channelOut --> channelOut[i];
            port[i].upperLayerOut --> relay.lowerLayerIn[i];
            port[i].upperLayerIn <-- relay.lowerLayerOut[i];
        }

}
