packet DataPacket {
    simtime_t genTime; //istante di generazione del pacchetto
    bool lastBurstPacket = false; //di default il pacchetto non e' l'ultimo del burst
};

//informazioni di controllo immesse dall'applicazione
message DataControlInfo { 
    string destination;
}