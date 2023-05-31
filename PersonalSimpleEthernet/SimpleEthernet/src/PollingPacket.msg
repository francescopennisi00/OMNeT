packet PollingRequest {
    
    //pollingBurst = numero di messaggi che si possono inviare sul canale con la richiesta polling
    int requestedFrames;
    
    //nome flusso (ogni PollingRequest si riferisce ad un certo flusso applicativo)
    string flow; 
    
    //priorita' di schedulazione delle polling request (quindi del traffico dalle varie applicazioni): + basso e' il valore, > e' la priorita'
    long priority; 
    
    uint64_t trxno; //numero di transazione per identificare la polling request e il polling data associato (campo a 8 byte)
    
    //8 (long generalmente a 64 bit) per priority, 8 per trxno, 4 per requestedFrames (int generalmente a 32 bit), 2 per il nome del flusso
    byteLength = 22;  
    
};

//messaggio che serve al Polling Controller
packet PollingData {
    string destination;//destinazione del burst di pacchetti generati dall'applicazione (cioe' la destinazione del pacchetto applicativo incapsulato)
    uint64_t trxno; //identificativo della transazione (richiesta di trasmissione con PollingRequest e trasmissione del dato nel PollingData)
    byteLength = 15;  //6 byte del MAC address + 8 byte del numero di transazione + 1 byte del campo last
    
    //flag settato a true solo per l'ultimo frame del burst (occupa 1 byte)
    //(ogni pacchetto corrisponde a un frame, quindi abbiamo un burst di pacchetti e un burst di frame) 
    bool last = false;  
};

//il master polling ha una tabella dei flussi che contiene in ogni entry:
//nome flusso, indirizzo di sorgente, burst size, periodo di trasmissione di un burst del flusso e deadline relativa
struct FlowTableEntry {
    string addr;  //indirizzo del nodo trasmittente il flusso
    string flow;
    int burst; //burst size del flusso
    simtime_t period;
    simtime_t deadline; //deadline relativa dell'intero flusso
};

//definisco la classe che, incapsulando un array di FlowTableEntry, modella l'intera tabella dei flussi
class FlowTableParameters extends cOwnedObject {
    FlowTableEntry flows[];
};