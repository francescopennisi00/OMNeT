package simpleethernet;

simple PollingLayer {
    parameters:
    	@display("i=block/timer");
    	int burstSize;
    	string flow;
    	string controllerAddress;
    	
    	@signal[PollingQueueSize];
    	@statistic[PollingQueueSize](record=vector);
    gates:
        input lowerLayerIn;
        output lowerLayerOut;
        input upperLayerIn;
        output upperLayerOut;
}
