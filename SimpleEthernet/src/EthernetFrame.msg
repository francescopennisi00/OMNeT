//inglobiamo il contenuto informativo utile in un frame Ethernet, che il livello MAC passa al livello fisico
packet EthernetFrame {
    string dst;
    string src;
    
    //dimensione del frame 
    //(senza payload, modellizzato in un oggetto ApplicationPacket che però non contiene reale payload)
    byteLength=26; 
                    
    //il preambolo e' nella struttura del frame ma e' aggiunto a livello fisico, non in questo livello
    //il campo FCS non viene incluso perché in Omnetpp c'e' gia' un controllo sui bit di un packet
    
    int etherType; //tipologia Ethernet, non c'e' un campo apposito nella struttura del Frame
    
    
}