package simpleethernet;

simple EthernetPhy
{
    parameters:
        double datarate @unit(bps) = default(1Gbps);
        @display("i=block/mac");
        
        //questa statistica ci permette di capire se la rete è in saturazione: 
        //arrivano frame da trasmettere piu' velocemente di quanto velocemente svuotiamo la coda di trasmissione
        @signal[QueueSize];
        //registriamo max così sappiamo di quanto le varie code per ogni livello fisico (di host o switch) si riempiono al massimo 
        //(se -> +inf siamo in saturazione)
        @statistic[QueueSize](record=vector,max); 
        
    gates:
        output upperLayerOut;
        input upperLayerIn;
        output channelOut;
        input channelIn;
}
