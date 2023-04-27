package simpleethernet;

simple RelayUnit  //gestisce l'inoltro di tutti i pacchetti che giungono allo switch
{
    parameters:
        int relayPortCount; //avrà un numero di porte pari al numero porte switch (portCount)
        @display("i=block/switch");
        //[ { addr: "nodename", port: int }, { addr: "nodename", port: int } ];
        object staticEntries; //entries statiche (di configurazione)
    gates:
        output lowerLayerOut[relayPortCount];
        input lowerLayerIn[relayPortCount];
}
