package simpleethernet;

module EthernetHost
{
    parameters:
        int appCount = default(1); //quante applicazioni sono attive in un host (quindi quanti sono i PollingLayer)
        @display("bgb=841,444;i=device/device");
        bool isPollingMaster = default(false);

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
        pollingLayer[appCount]: PollingLayer {
            @display("p=85,140,r,70");
        }
        pollingMaster: PollingMaster if isPollingMaster  == true {
            @display("p=672,88;i=block/star");
        }
    connections:
        dispatcher.lowerLayerOut --> eth.upperLayerIn;
        eth.upperLayerOut --> dispatcher.lowerLayerIn;
        channelIn --> eth.channelIn;
        eth.channelOut --> channelOut;
        //collegamento delle varie applicazioni con il polling layer relativo e dei vari polling layer con il disptcher
        for i=0..appCount-1 {
            pollingLayer[i].lowerLayerOut --> dispatcher.upperLayerIn++;
            pollingLayer[i].lowerLayerIn <-- dispatcher.upperLayerOut++;
            app[i].lowerLayerOut --> pollingLayer[i].upperLayerIn;
            app[i].lowerLayerIn <-- pollingLayer[i].upperLayerOut;
        }
        pollingMaster.lowerLayerOut --> dispatcher.upperLayerIn++ if isPollingMaster == true;
        dispatcher.upperLayerOut++ --> pollingMaster.lowerLayerIn if isPollingMaster == true;
}
