package simpleethernet;

//modulo inserito entro un unico host che avrà il ruolo di Polling Master dedicato alla schedulazione dei flussi dei vari host della
//rete con politica EDF o qualunque altra (possiamo facilmente modificare la politica adottata dal master). 
//Esso deve andare volta per volta interrogare ogni nodo per ogni flusso in base alla schedulazione tramite delle Polling Request

simple PollingMaster
{
     parameters:
        //possiede una tabella dei flussi, usata per schedularli
        object flowTable = default(FlowTableParameters { flows: [] });
        
        string schedPolicy @enum("EDF","DM","FIFO") = default("DM");  //diverse politiche di scheduling ammesse
        
        //se entro 1 ms non e' tornato niente indietro da parte del nodo a cui ho inviato la polling request, assumo che esso non abbia niente da trasmettere
        //trxTimer indica la durata del periodo di attesa: appena arrivera' al modulo PollingMaster l'evento timer associato (scadenza del timer stesso)
        //il master sapra' che il nodo non aveva nulla da trasmettere o ha ritardato troppo la trasmissione sforando il tempo ad esso riservato
        double trxTimer @unit(s) = default(1ms); //abbiamo poi visto che serve 117 us
        
        @signal[TrxTime];
        @statistic[TrxTime](record=vector);
        
     gates:      
         //il pollig master e' al livello piu' alto dell'host master (non ci sono porte verso l'alto)
         output lowerLayerOut;
         input lowerLayerIn;
}
