packet DataPacket {
    simtime_t genTime;
    uint64_t seqno;
    bool lastBurstPacket = false;
};

message DataControlInfo {
    string destination;
};
