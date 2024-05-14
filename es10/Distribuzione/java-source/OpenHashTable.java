import java.util.LinkedList;

public class OpenHashTable extends AbstractHashTable {
    // in teoria la scansione quadratica prevede la seguente formula per la sequenza di hash code
    // h(k, i) = (h'(k) + c1*i + c2 *i^2) mod m
    // con c1 e c2 coefficienti
    // m è l'indice massimo, quindi in teoria getSize()
    //in questp caso impostiamo c1 = 0 e c2 = 1
    // Un array di Entry per la tabella
    private Entry[] table;
    // Marcatore di cella vuota ma da esaminare durante probing
    private final Entry DEFUNCT = new Entry(null, 0); 
    
    /* Costruttori */
    public OpenHashTable(int cap, int p, double lambda) {
        super(cap, p, lambda);
    }

    public OpenHashTable(int cap, int p) {
        super(cap, p); // massimo fattore di carico predefinito
    }
    
    public OpenHashTable(int cap) {
        super(cap); // primo predefinito
    }
    
    public OpenHashTable() {
        super(); // capacità predefinita
    }
        
    /* Metodi non implementati in AbstractHashTable */

    // Inizializza una tabella hash vuota secondo i parametri passati al costruttore
    protected void createTable() {
        int n = getCapacity();
        table = new Entry[n];
        for(Entry e :table){
            e = null;
        }
        return;
    }

    // Restituisce il valore (intero) associato alla chiave k
    // Restituisce -1 se la chiave è assente
    public int get(String k) {
        //potenzialmente ci sono da aggiungere dei controlli
        int h = hashFunction(k);
        int idx = h;
        int i = 1;
        while(i < getCapacity()){ 
            if(table[idx] == null) return -1;
            if(table[idx].getKey() == k) return table[idx].getValue();
            idx = (h + i*i)%getCapacity();
            i++;
        }
        return -1;
    }
    
    // Aggiorna il valore associato alla chiave k
    // Restituisce il vecchio valore o -1 se la chiave non è presente
    public int put(String k, int value) {
        int h = hashFunction(k);
        int idx = h;
        int i = 1;
        int val = -1;
        int app = -1;
        //System.out.println("capacity: " + getCapacity());
        if( (double)((size() + 1) / getCapacity()) >= getMaxLambda()){
            resize(getCapacity()*2 + 1); //per mantenerlo dispari, secondo un teorema se è primo
                                         //dovrei aver garantito che non si ripetano gli indici
        }
        //System.out.println("chiamata put per k: " + k + " v: " + value );
        while(true){
            //System.out.println(idx);
            if(table[idx] == null){
                table[idx] = new Entry(k, value);
                System.out.println("inserisco: " + k + " all'indice: " + idx);
                incSize();
                break;
            }
            if(table[idx] == DEFUNCT && app == -1){
                //il primo defunct trovato viene memorizzato in modo da 
                //averlo nel caso in cui non si trova una cella con la stessa chiave
                app = idx;
            }
            if(table[idx].getKey() == k){
                val = table[idx].getValue();
                table[idx].setValue(value);
                app = -1;
                break;
            }
            if(i == getCapacity()) {
                System.out.println("raggiunta capacità massima, molto strano");
                break;}
            idx = (h + i*i)%getCapacity();
            i++;
        }
        if(app != -1){
            table[app].setValue(value);
        }

        return val;
    }
    
    // Rimuove la coppia con chiave k
    // Restituisce il vecchio valore o -1 se la chiave non è presente
    public int remove(String k) {
        int h = hashFunction(k);
        int idx = h;
        int i = 1;
        int val = -1;
        //System.out.println("capacity: " + getCapacity());
        if( (double)((size() + 1) / getCapacity()) >= getMaxLambda()){
            resize(getCapacity()*2 + 1); //per mantenerlo dispari, secondo un teorema se è primo
                                         //dovrei aver garantito che non si ripetano gli indici
        }
        //System.out.println("chiamata put per k: " + k + " v: " + value );
        while(i < getCapacity()){
            //System.out.println(idx);
            if(table[idx] == null)break;
            if(table[idx].getKey() == k){
                val = table[idx].getValue();
                table[idx] = DEFUNCT;
                decSize();
                break;
            }
            idx = (h + i*i)%getCapacity();
            i++;
        }
        return val;
    }
    
    // Restituisce un oggetto Iterable contenente tutte le coppie presenti nella tabella hash
    public Iterable<Entry> entrySet() {
        LinkedList<Entry> it = new LinkedList<Entry>();
        for(Entry e: table){
            if(e!= null && e.getKey() != null)
                it.add(e);
        }
        return it;
    }
}
