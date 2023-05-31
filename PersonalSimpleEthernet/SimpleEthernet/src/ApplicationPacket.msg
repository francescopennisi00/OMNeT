packet DataPacket {
    simtime_t genTime; //istante di generazione del pacchetto
    bool lastBurstPacket = false; //di default il pacchetto non e' l'ultimo del burst
    uint64_t seqno; //numero di sequenza
};

//informazioni di controllo immesse dall'applicazione
message DataControlInfo { 
    string destination;
}