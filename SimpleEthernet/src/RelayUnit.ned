package simpleethernet;

simple RelayUnit
{
    parameters:
        @display("i=block/switch");
        int relayPortCount;
        //[ { addr: "nodename", port: int }, { addr: "nodename", port: int } ];
        object staticEntries = default(StaticRelayEntries { entries: [] });
    gates:
        input lowerLayerIn[relayPortCount];
        output lowerLayerOut[relayPortCount];
}
