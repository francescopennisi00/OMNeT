package simpleethernet.simulations;

import simpleethernet.EthernetHost;
import simpleethernet.EthernetSwitch;
import simpleethernet.TrafficGen;


network SimpleEthernetNet
{
    parameters:
        @display("bgb=741,335");
        double netber = default(0); //di default la rete non ha BER

        //non modificabile nel file .ini (la priorita' nei valori dei parametri e' sul file .ned rispetto al file .ini, 
        //tranne se si usa default nel file .ned, ma in questo caso non lo facciamo)
        **.portCount = 3; //vale per tutti gli switch

    submodules:
        switch0: EthernetSwitch {
            @display("p=241,159");
        }
        switch1: EthernetSwitch {
            @display("p=421,179");
        }
        host0: EthernetHost {
            @display("p=108,73");
        }
        host1: EthernetHost {
            @display("p=96,184");
        }
        host2: EthernetHost {
            @display("p=560,270");
        }
        host3: EthernetHost {
            @display("p=514,67");
        }
    connections:
        //impostiamo la BER su tutte le porte
        //switch0.channelOut[0] --> {ber = parent.netber;} -->  switch1.channelIn[0];
        //switch1.channelOut[0] --> {ber = parent.netber;} --> switch0.channelIn[0];
        //switch0.channelOut[1] --> {ber = parent.netber;} -->  host0.channelIn;
        //host0.channelOut --> {ber = parent.netber;} -->  switch0.channelIn[1];
        //switch0.channelOut[2] --> {ber = parent.netber;} -->  host1.channelIn;
        //host1.channelOut --> {ber = parent.netber;} -->  switch0.channelIn[2];
        //switch1.channelOut[1] --> {ber = parent.netber;} -->  host2.channelIn;
        //host2.channelOut --> {ber = parent.netber;} -->  switch1.channelIn[1];
        //host3.channelOut --> {ber = parent.netber;} -->  switch1.channelIn[2];
        //switch1.channelOut[2] --> {ber = parent.netber;} -->  host3.channelIn;
        switch0.channelOut[0] --> switch1.channelIn[0];
        switch1.channelOut[0] --> switch0.channelIn[0];
        switch0.channelOut[1] --> host0.channelIn;
        host0.channelOut --> switch0.channelIn[1];
        switch0.channelOut[2] --> host1.channelIn;
        host1.channelOut --> switch0.channelIn[2];
        switch1.channelOut[1] --> host2.channelIn;
        host2.channelOut --> switch1.channelIn[1];
        host3.channelOut --> switch1.channelIn[2];
        switch1.channelOut[2] --> host3.channelIn;
}
