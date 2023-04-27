package simpleethernet;

//MODULO APPLICAZIONE GENERATRICE DI TRAFFICO

simple TrafficGen
{
    parameters:
       @display("i=block/app2");
       int payloadLength @unit(B);
       volatile double period @unit(s); //volatile perche' vorremmo generare anche traffico aperiodico
       string destination; //uso una stringa come indirizzo, non il MAC che e' piu' complesso da ricordare
       double startTime @unit(s) = default(-1s); //se -1, il nodo non genera traffico (nodo 1 non deve farlo)
       int burstSize = default(1); //numero di frame di dimensione payloadLength generate in un burst
       string flow; //nome di flusso per distinguere le statistiche da vari flussi
    
       //statistiche da catturare a livello di modulo applicazione (TrafficGen)
       @signal[EtoEDelay];
       @signal[BurstEtoEDelay];
       @signal[SigThroughput];
       
       @statistic[EtoEDelay](record=vector);
       @statistic[BurstEtoEDelay](record=vector);
       @statistic[SigThroughput](record=vector,last);
    
    gates:
        output lowerLayerOut;
        input lowerLayerIn;
}
