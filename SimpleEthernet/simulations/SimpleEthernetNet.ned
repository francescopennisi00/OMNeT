package simpleethernet.simulations;

import simpleethernet.EthernetHost;
import simpleethernet.EthernetSwitch;
import simpleethernet.TrafficGen;


network SimpleEthernetNet
{
    parameters:
        @display("bgb=925.275,498.225");
        double netber = default(0);
        SW1.portCount = 11;
        SW2.portCount = 10;
    submodules:
        SW1: EthernetSwitch {
            @display("p=347.21375,231.08875");
        }
        SW2: EthernetSwitch {
            @display("p=560.8837,231.08875");
        }
        LD2: EthernetHost {
            @display("p=129.21,105.12;i=device/satellite");
        }
        CM1: EthernetHost {
            @display("p=90.5775,279.86124;i=device/port");
        }
        LD1: EthernetHost {
            @display("p=104.5125,363.47125;i=device/satellite");
        }
        US2: EthernetHost {
            @display("p=90.5775,185.8;i=block/classifier2");
        }
        US1: EthernetHost {
            @display("p=142.83374,442.43625;i=block/classifier2");
        }
        S2: EthernetHost {
            @display("p=270.57126,85.932495;i=block/wtx");
        }
        S1: EthernetHost {
            @display("p=238.05624,330.95624;i=block/wtx");
        }
        CU: EthernetHost {
            @display("p=202.0575,179.99374;i=device/cpu");
        }
        HU: EthernetHost {
            @display("p=395.98624,314.69873;i=device/pc");
        }
        S4: EthernetHost {
            @display("p=685.1375,81.2875;i=block/wtx");
        }
        S3: EthernetHost {
            @display("p=697.91125,385.535;i=block/wtx");
        }
        RS1: EthernetHost {
            @display("p=560.8837,147.47874;i=old/telnet");
        }
        RS2: EthernetHost {
            @display("p=575.98,337.92374;i=old/telnet");
        }
        RC: EthernetHost {
            @display("p=832.6162,229.92749;i=device/port");
        }
        ME: EthernetHost {
            @display("p=730.4262,166.05875;i=misc/node");
        }
        TLM: EthernetHost {
            @display("p=780.36,314.69873;i=device/antennatower");
        }
        US4: EthernetHost {
            @display("p=838.4225,399.47;i=block/classifier2");
        }
        US3: EthernetHost {
            @display("p=840.745,62.7075;i=block/classifier2");
        }
        MasterNode: EthernetHost {
            @display("p=447.08124,45.28875;i=old/comp_a");
        }
    connections:
        //switch0.channelOut[0] --> switch1.channelIn[0];
        //switch1.channelOut[0] --> switch0.channelIn[0];
        //switch0.channelOut[1] --> host0.channelIn;
        //host0.channelOut --> switch0.channelIn[1];
        //switch0.channelOut[2] --> host1.channelIn;
        //host1.channelOut --> switch0.channelIn[2];
        //switch1.channelOut[1] --> host2.channelIn;
        //host2.channelOut --> switch1.channelIn[1];
        //host3.channelOut --> switch1.channelIn[2];
        //switch1.channelOut[2] --> host3.channelIn;

        S1.channelOut --> SW1.channelIn[0];
        SW1.channelOut[0] --> S1.channelIn;
        CU.channelOut --> SW1.channelIn[1];
        SW1.channelOut[1] --> CU.channelIn;
        SW1.channelOut[2] --> S2.channelIn;
        S2.channelOut --> SW1.channelIn[2];
        SW1.channelOut[3] --> LD2.channelIn;
        LD2.channelOut --> SW1.channelIn[3];
        CM1.channelOut --> SW1.channelIn[4];
        SW1.channelOut[4] --> CM1.channelIn;
        US2.channelOut --> SW1.channelIn[5];
        SW1.channelOut[5] --> US2.channelIn;
        US1.channelOut --> SW1.channelIn[6];
        SW1.channelOut[6] --> US1.channelIn;
        HU.channelOut --> SW1.channelIn[7];
        SW1.channelOut[7] --> HU.channelIn;
        LD1.channelOut --> SW1.channelIn[8];
        SW1.channelOut[8] --> LD1.channelIn;
        RS1.channelOut --> SW2.channelIn[0];
        SW2.channelOut[0] --> RS1.channelIn;
        SW2.channelOut[1] --> RS2.channelIn;
        RS2.channelOut --> SW2.channelIn[1];
        S3.channelOut --> SW2.channelIn[2];
        SW2.channelOut[2] --> S3.channelIn;
        SW2.channelOut[3] --> S4.channelIn;
        S4.channelOut --> SW2.channelIn[3];
        SW2.channelOut[4] --> ME.channelIn;
        ME.channelOut --> SW2.channelIn[4];
        SW2.channelOut[5] --> RC.channelIn;
        RC.channelOut --> SW2.channelIn[5];
        SW2.channelOut[6] --> TLM.channelIn;
        TLM.channelOut --> SW2.channelIn[6];
        SW2.channelOut[7] --> US4.channelIn;
        US4.channelOut --> SW2.channelIn[7];
        SW2.channelOut[8] --> US3.channelIn;
        US3.channelOut --> SW2.channelIn[8];
        SW1.channelOut[9] --> SW2.channelIn[9];
        SW2.channelOut[9] --> SW1.channelIn[9];
        MasterNode.channelOut --> SW1.channelIn[10];
        SW1.channelOut[10] --> MasterNode.channelIn;
        
}
