package simpleethernet;

module EthernetInterface
{
    @display("bgb=774,452;i=block/ifcard");

    gates:
        output channelOut;
        input channelIn;
        output upperLayerOut;
        input upperLayerIn;

    submodules:
        dll: EthernetDataLink {
            @display("p=379,117");
        }
        phy: EthernetPhy {
            @display("p=379,300");
        }

    connections:
        dll.lowerLayerOut --> phy.upperLayerIn;
        phy.upperLayerOut --> dll.lowerLayerIn;
        dll.upperLayerOut --> upperLayerOut;
        upperLayerIn --> dll.upperLayerIn;
        phy.channelOut --> channelOut;
        channelIn --> phy.channelIn;
}
