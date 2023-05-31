package simpleethernet;

//questo simple module e' collocato all'interno di un host tra una applicazione (TrafficGen) e il dispatcher:
//ne avremo uno per ogni applicazione, per cui ci sara', all'interno di un EthernetHost, un array di appCount PollingLayer

//in pratica, cio' che fa questo livello e' gestire una coda di trasmissione per i pacchetti che l'applicazione deve inviare nella
//rete: il traffico proveniente da una applicazione, prima di essere trasmesso, e' inserito all'interno di una coda FIFO.
//Questa coda modella il fatto che una applicazione qualsiasi non puo' riuscire a immettere traffico nella rete a velocita'
//inifinita, ma possiede una velocita' massima di smaltimento del traffico da trasmettere: pertanto, se i dati da trasmettere si
//presentano con una velocita' maggiore di quella di svuotamento della coda di trasmissione, c'e' il rischio che l'applicazione
//entri in saturazione, causando una perdita di pacchetti a causa dell'overflow del buffer di trasmissione.
//Questo perche' a dettare la reale trasmissione dei pacchetti da parte dell'applicazione non e' la stessa applicazione, ma la schedulazione
//della rete stessa, comandata da un componente dedicato allo scheduling, appunto, detto polling master o controller

//la gestione della coda viene fatta, appunto, tramite polling: periodicamente, viene estratto dalla coda un burst di pacchetti da trasmettere
//il numero di pacchetti che compongono il burst di estrazione dalla coda e' in generale diverso da quello di immissione nella coda 
//stessa, cioe' del numero di pacchetti che compongono il burst generato periodicamente dall'applicazione, cosi' come sono
//in generale diversi il periodo di trasmissione e quello di polling. Nella pratica potremmo assumere a due a due questi valori uguali,
//ma dipende dalle scelte di schedulazione del traffico del PollingMaster

//l'estrazione, infatti, avviene quando al polling layer di una applicazione giunge una polling request comandata dal controller 
//o polling master, che e' un componente dedicato ad effettuare la schedulazione della trasmissione dei flussi delle varie applicazioni, 
//collocato all'interno di un solo host che gioca il ruolo di Master, appunto

simple PollingLayer
{
    parameters:
        
        @display("i=block/timer");
        
        // <= a quello dell'applicazione (se < potremmo saturare a meno che periodo polling < periodo trasmissione, ma avrebbe poco senso)
        int burstSize; 
        string flow; //identificativo del flusso dati inviato e/o ricevuto dall'applicazione relativa al PollingLayer
        
        //indirizzo dell'host che contiene il PollingMaster (entro un unico host) dedicato ad effettuare lo scheduling 
        //del traffico generato da tutte le applicazioni
        string controllerAddress; 
        
        
        @signal[PollingQueueSize];
        @statistic[PollingQueueSize](record=vector);
        
    gates:
        
        //porte di collegamento al dispatcher (unico entro l'host)
        input lowerLayerIn;
        output lowerLayerOut;
        
        //porte di collegamento al singolo modulo applicazione TrafficGen relativo al singolo modulo PollingLayer
        input upperLayerIn;
        output upperLayerOut;
}
