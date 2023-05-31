package simpleethernet;

//MODULO APPLICAZIONE GENERATRICE DI TRAFFICO

simple TrafficGen
{
    parameters:
       @display("i=block/app2");
       int payloadLength @unit(B);
       volatile double period @unit(s); //volatile (il cui valore puo' cambiare nel tempo) perche' vorremmo generare anche traffico aperiodico
       string destination; //stringa percorso dell'interfaccia Ethernet dell'host di destinazione, non il MAC address, + complesso da ricordare
       double startTime @unit(s) = default(-1s); //se -1, il nodo non genera traffico
       int burstSize = default(1); //numero di frame di dimensione payloadLength generate in un burst
       string flow; //nome di flusso per distinguere le statistiche dei vari flussi
    
       //statistiche da catturare a livello di modulo applicazione (TrafficGen)
       @signal[EtoEDelay];
       @signal[BurstEtoEDelay];
       @signal[SigThroughput];
       //indica la percentuale di pacchetti, quindi di frame, persi in ricezione sul totale che erano stati inviati all'applicazione
       @signal[FLR]; //FLR sta per Frame Loss Ratio
       
       @statistic[EtoEDelay](record=vector);
       @statistic[BurstEtoEDelay](record=vector);
       @statistic[SigThroughput](record=vector, last);
       @statistic[FLR](record=vector, last);
    
    gates:
        output lowerLayerOut;
        input lowerLayerIn;
}
