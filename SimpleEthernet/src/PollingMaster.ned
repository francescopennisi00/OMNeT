package simpleethernet;

simple PollingMaster
{
    parameters:
        object flowTable = default(FlowTableParameters { flows: [] });
        string schedPolicy @enum("EDF","DM","FIFO") = default("FIFO");
        double trxTimer @unit(s) = default(1ms);
        @display("i=block/cogwheel");
        
        @signal[TrxTime];
        @statistic[TrxTime](record=vector);
    gates:
        output lowerLayerOut;
        input lowerLayerIn;
}
