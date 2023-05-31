package simpleethernet;

module EthernetSwitch
{
    parameters:
        @display("bgb=794,406;i=device/hub");
        int portCount = default(4); //4 porte dello switch (4 input e 4 output): 4 simple module EthernetPhy contenute nel modulo EthernetSwitch

    gates:  //connesse direttamente al canale
        input channelIn[portCount];
        output channelOut[portCount];

    submodules:
        port[portCount]: EthernetPhy {
            @display("p=148,220");
        }
        relay: RelayUnit {
            @display("p=501,208");
            //setto i parametri della precisa istanza del RelayUnit
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
