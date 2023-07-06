packet PollingRequest {
    string flow;
    int requestedFrames;
    long priority;
    uint64_t trxno;
    byteLength = 22;
};

packet PollingData {
    string destination;
    uint64_t trxno;
    bool last = false;
    byteLength = 15;
};

struct FlowTableEntry {
    string flow;
    string addr;
    int burst;
    simtime_t period;
    simtime_t deadline;
};

class FlowTableParameters extends cOwnedObject {
    FlowTableEntry flows[];
};