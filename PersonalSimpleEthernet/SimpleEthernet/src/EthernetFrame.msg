//inglobiamo il contenuto informativo utile in un frame Ethernet, che il livello MAC (DataLink) passa al livello fisico
packet EthernetFrame {
    string dst;
    string src;
    
    //dimensione del frame in bytes (12 per source e destination MAC addresses, 2 per EtherType/Len, 4 per il CRC e 8 per il preambolo)
    //(senza payload, modellizzato in un oggetto DataPacket che però non contiene reale payload)
    byteLength=26; 
                    
    //il preambolo e' nella struttura del frame ma e' aggiunto a livello fisico, non nel MAC (quindi non mettiamo un campo per esso)
    //il campo FCS non viene incluso perché in Omnetpp c'e' gia' un controllo sui bit di un packet
    //comunque, nella dimensione della frame, li abbiamo contati)
    
    int etherType; //tipologia Ethernet, non c'e' un campo apposito nella struttura del Frame
}

//definiamo una riga statica della tabella di forwarding (all'interno della RelayUnit di uno switch)
//(rispetto ad un entries generica, definita in RelayUnit.h, mancano due campi che servono solo a distinguere se una entry e'
//statica o no: non inseriamo questi due campi in questa definizione di struct in modo che,
//quando indichiamo nel file .ini i parametri di queste entries statiche di tipo RelayTableEntry 
//dentro un oggetto della classe StaticRelayTableEntries, mettiamo solamente l'indirizzo e la porta associata
struct RelayTableEntry {
   string addr;
   int port;
};

//DEFINIAMO UNA CLASSE CHE CONTERRA' UN ARRAY DI ENTRIES (CIOE' LE ENTRIES STATICHE DELLA TABELLA DI FORWARDING)
class StaticRelayEntries extends cOwnedObject {
    RelayTableEntry entries[]; //PER DICHIARARE UN ARRAY DENTRO I FILE .msg BISOGNA INCAPSULARE L'ARRAY IN UNA CLASSE
}
        