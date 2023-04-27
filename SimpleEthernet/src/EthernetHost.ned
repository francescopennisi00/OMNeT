package simpleethernet;

module EthernetHost
{

    parameters:
        int appCount = default(1); //quanto applicazioni sono attive in un host
        @display("bgb=841,444;i=device/pc");
            
    gates:
        input channelIn;
        output channelOut;

    submodules:
        app[appCount]: TrafficGen {
            @display("p=118,54");
        }
        dispatcher: ApplicationDispatcher {
            @display("p=325,170");
        }
        eth: EthernetInterface {
            @display("p=405,341");
        }
    connections:
        dispatcher.lowerLayerOut --> eth.upperLayerIn;
        eth.upperLayerOut --> dispatcher.lowerLayerIn;
        channelIn --> eth.channelIn;
        eth.channelOut --> channelOut;
        //collegamento delle varie applicazioni con il dispatcher
        for i=0 .. appCount-1 {
            app[i].lowerLayerOut --> dispatcher.upperLayerIn++;
            dispatcher.upperLayerOut++ --> app[i].lowerLayerIn;
        }
}
