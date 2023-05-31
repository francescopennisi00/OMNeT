package simpleethernet;

simple RelayUnit  //gestisce l'inoltro di tutti i pacchetti che giungono allo switch usando la tabella di forwarding
{
    parameters:
        
        //avrà un numero di porte pari al numero porte dello switch (che e' portCount): ogni porta del relayPortCount comunica
        //con uno dei livelli fisici dello switch (esso ne ha uno per ogni sua porta)
        int relayPortCount; // = portCount: le porte in realtà saranno 2*portCount infatti distinguiamo quelle di input e di output
        
        @display("i=block/switch");
        
        //entries statiche (di configurazione) della tabella di forwarding: 
        //hanno una stringa (nodename) per indirizzo e un'indice del vettore di porte come porta associata all'indirizzo stesso
        
        //[ { addr: "nodename", port: int }, { addr: "nodename", port: int } ];
        object staticEntries = default(StaticRelayEntries { entries: [] }); 
        
    gates:
        output lowerLayerOut[relayPortCount];
        input lowerLayerIn[relayPortCount];
}
