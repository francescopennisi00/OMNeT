package simpleethernet.simulations;

import simpleethernet.EthernetHost;
import simpleethernet.TrafficGen;


network SimpleEthernetNet
{
    @display("bgb=741,335");
    submodules:
        host1: EthernetHost {
            @display("p=154,107");
        }
        host2: EthernetHost {
            @display("p=558,178");
        }
    connections:
        host1.channelOut --> host2.channelIn;
        host2.channelOut --> host1.channelIn;
}
