import java.util.LinkedList;

import javax.swing.table.TableModel;

import java.util.ArrayList;

public class ChainHashTable extends AbstractHashTable {
    // Un array di LinkedList per le liste di trabocco 
    private LinkedList<Entry> [] table;
    
    /* Costruttori */
    public ChainHashTable(int cap, int p, double lambda) {
        super(cap, p, lambda);
    }
    
    public ChainHashTable(int cap, int p) {
        super(cap, p); // massimo fattore di carico predefinito
    }
    
    public ChainHashTable(int cap) {
        super(cap); // primo predefinito
    }
    
    public ChainHashTable() {
        super(); // capacità predefinita
    }
    
    /* Metodi non implementati in AbstractHashTable */

    // Inizializza una tabella hash vuota secondo i parametri passati al costruttore
    protected void createTable() {
        int n = getCapacity();
        table = new LinkedList[n];
        for(int i = 0; i < n; i++){
            table[i] = new LinkedList<Entry>();
        }

        return;
    }

    // Restituisce il valore (intero) associato alla chiave k
    // Restituisce -1 se la chiave è assente
    public int get(String k) {
        int idx = this.hashFunction(k);
        try{
            for(Entry n : table[idx]){
                if(n.getKey() == k){
                    return n.getValue();
                }
            }
        }
        catch(IndexOutOfBoundsException e){

        }
        return -1;
    }
    
    // Aggiorna il valore associato alla chiave k (o inserisce una nuova coppia se la chiave non è presente)
    // Restituisce il vecchio valore o -1 se la chiave non è presente
    public int put(String k, int value) {
        int idx = this.hashFunction(k);
        int val = -1;
        if((double)(size() + 1 ) / getCapacity() >= getMaxLambda()){
             resize(getCapacity() * 2);
         }
        try{
            for(Entry n : table[idx]){
                if(n.getKey() == k){
                    val = n.getValue();
                    n.setValue(value);
                    return val;
                }
            }
            table[idx].add(new Entry(k, value));
            incSize();
        }
        catch(IndexOutOfBoundsException e){
           System.err.println("la capacità è inferiore a quella richiesta idx = " +  idx); 
        }
        return val;
    }
    
    // Rimuove la coppia con chiave k
    // Restituisce il vecchio valore o -1 se la chiave non è presente
    public int remove(String k) {
        int idx = this.hashFunction(k);
        int val = -1;
        try{
            for(Entry n : table[idx]){
                if(n.getKey() == k){
                    val = n.getValue();
                    table[idx].remove(n);
                    return val;
                }
            }
            decSize();
        }
        catch(IndexOutOfBoundsException e){
           System.err.println("la capacità è inferiore a quella richiesta: idx = " + idx); 
        }
        return val;
    }
    
    // Restituisce un oggetto Iterable contenente tutte le coppie presenti nella tabella hash
    public Iterable<Entry> entrySet() {
        LinkedList<Entry> set = new LinkedList<Entry>();
        for(LinkedList<Entry> i: table){
            for(Entry e :i){
                set.add(e);
            }
        }
        return set;
    }
}
