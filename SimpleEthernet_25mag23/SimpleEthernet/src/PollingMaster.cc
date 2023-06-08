#include "PollingMaster.h"
#include "ApplicationPackets_m.h"

Define_Module(PollingMaster);

void PollingMaster::initialize() {
    pollQueue = cPacketQueue(0, poll_queue_comp);
    flowTable = check_and_cast<FlowTableParameters *>(par("flowTable").objectValue());
    ongoingTransaction = false;

    trxTimer = new cMessage("TrxTimer");
    trxno = 0;

    sigTrxTime = registerSignal("TrxTime");

    for(int i=0; i < flowTable->getFlowsArraySize(); i++) {
        cMessage *tmr = new cMessage("PollTimer");
        tmr->setKind(i);
        scheduleAt(flowTable->getFlows(i).period, tmr);
    }
}

void PollingMaster::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {
        if(strcmp(msg->getName(), "PollTimer") == 0) {
            PollingRequest *pr = new PollingRequest("PollingRequest");
            int i = msg->getKind();
            EV_DEBUG <<"Stampa i: " <<i<<endl;
            FlowTableEntry f = flowTable->getFlows(i);
            EV_DEBUG <<" Stampa f: " << f.addr <<endl;
            pr->setFlow(f.flow.c_str());
            pr->setRequestedFrames(f.burst);
            if(strcmp(par("schedPolicy").stringValue(), "DM") == 0) {
                pr->setPriority(f.deadline.inUnit(SimTimeUnit::SIMTIME_US));
            } else if(strcmp(par("schedPolicy").stringValue(), "EDF") == 0) {
                long d = (f.deadline+simTime()).inUnit(SimTimeUnit::SIMTIME_US);
                pr->setPriority(d);
            } else {
                pr->setPriority(0);
            }
            DataControlInfo *ci = new DataControlInfo();
            ci->setDestination(f.addr.c_str());
            pr->setControlInfo(ci);
            pollQueue.insert(pr);
            sendNextPollRequest();
            scheduleAt(simTime()+f.period, msg);
            return;
        } else if(strcmp(msg->getName(), "TrxTimer") == 0) {
            EV_INFO << "Transazione non completata in tempo" << endl;
            ongoingTransaction = false;
            sendNextPollRequest();
            return;
        }
    }

    PollingData *pd = dynamic_cast<PollingData *>(msg);
    if(pd != nullptr) {
        if(pd->getTrxno() != trxno) {
            error("Pacchetto arrivato fuori tempo massimo!");
        }
        emit(sigTrxTime, simTime()-txTime);
        cPacket *to_send = pd->decapsulate();
        DataControlInfo *ci = new DataControlInfo();
        ci->setDestination(pd->getDestination());
        to_send->setControlInfo(ci);
        if(pd->getLast()) {
            ongoingTransaction = false;
            cancelEvent(trxTimer);
        }
        delete pd;
        send(to_send, "lowerLayerOut");
        sendNextPollRequest();
        return;
    }

    delete msg;
}

void PollingMaster::sendNextPollRequest() {
    if(!ongoingTransaction && !pollQueue.isEmpty()) {
        ongoingTransaction = true;
        PollingRequest *pr = check_and_cast<PollingRequest *>(pollQueue.pop());
        trxno++;
        pr->setTrxno(trxno);
        txTime = simTime();
        send(pr, "lowerLayerOut");
        scheduleAt(simTime()+par("trxTimer"), trxTimer);
    }
}

int PollingMaster::poll_queue_comp(cObject *a, cObject *b) {
    PollingRequest *ta = check_and_cast<PollingRequest *>(a);
    PollingRequest *tb = check_and_cast<PollingRequest *>(b);

    return (tb->getPriority()-ta->getPriority()); //L'abbiamo rivalutata ed è corretta
}
