import java.util.*;

class Node<V> {
    private int key;
    private V value;
    private Node<V> left;
    private Node<V> right;
    private Node<V> p;
    public Node(int key, V value) {
        this.key = key;
        this.value = value;
    }
    public int getKey(){
        return key;
    }
    public V getValue(){
        return value;
    }
    public Node<V> getL(){
        return left;
    }
    public Node<V> getR(){
        return right;
    }
    public void setR(Node<V> n){
        right = n;
    }
    public void setL(Node<V> n){
        left = n;
    }
    public Node<V> getP() {
        return p;
    }
    public void setP(Node<V> n){
        p = n;
    }
    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object n){
        if(n.getClass() == Node.class && ((Node<V>)n).getKey() == key) return true;
        return false;
    }
}

public class BST<V> {
    Node<V> root;
    public BST(int key, V value) {
        root = new Node<V>(key, value); 
    }

    public void insert(int k, V v) {
        Node<V> z = new Node<V>(k, v);
        Node<V> x = root;
        Node<V> y = null;
        while(x != null){
            y = x;
            if(k < y.getKey()){
                x = y.getL();
            }
            else{
                x = y.getR();
            }
        }
        z.setP(y);
        if(y == null){
            root = z;
        }
        else if(k < y.getKey()){
            y.setL(z);
        }
        else{
            y.setR(z);
        }
        return;
    }

    public V find(int k) {
        Node<V> x = root;
        while(x != null && k != x.getKey()){
            if(k < x.getKey()){
                x = x.getL();
            }
            else{
                x = x.getR();
            }
        }
        if(x == null) return null;
        return x.getValue();
    }

    public int findMin() {
        Node<V> x = root;
        while(x.getL() != null){
            x = x.getL();
        }
        return x.getKey();
    }

    public void removeMin() {
        Node<V> x = root;
        while(x.getL() != null){
            x = x.getL();
        }
        x = null;
    }

    private void trasplant(Node<V> u, Node<V> v){
        if(u.getP() == null){
            root = v;
        }
        else if(u.equals(u.getP().getL())){
            u.getP().setL(v);
        }
        else{
            u.getP().setR(v);
        }
        if(v != null){
            v.setP(u.getP());
        }
    }

    private Node<V> minimum(Node<V> x){
        if(x == null) return null;
        while(x.getL() != null){
            x = x.getL();
        }
        return x;
    }

    private Node<V> findNode(int k){
        Node<V> x = root;
        while(x != null && k != x.getKey()){
            if(k < x.getKey()){
                x = x.getL();
            }
            else{
                x = x.getR();
            }
        }
        return x;
    }

    public void remove(int k) {
        Node<V> z = findNode(k);
        if(z == null){
            System.err.println("trovato null");
            return;
        }
        if(z.getL() == null){
            trasplant(z, z.getR());
        }
        else if(z.getR() == null){
            trasplant(z, z.getL());
        }
        else{
            Node<V> y = minimum(z.getR()); 
            if(y != z.getR()){
                trasplant(y, y.getR());
                y.setR(z.getR());
                y.getR().setP(y);
            }
            trasplant(z, y);
            y.setL(z.getL());
            y.getL().setP(y);
        }
        return;
    }

    private void recPrint(Node<V> x){
        if(x == null) return;
        recPrint(x.getL());
        System.out.print(x.getKey() + " ");
        recPrint(x.getR());
    }

    void print(){
        Node<V> x = root;
        //chiamo una print ricorsiva a partire dal nodo
        recPrint(x);
        System.out.println();
        return;
    }

    int predecessor(int k) {
        Node<V> v = findNode(k);
        Node<V> y;
        if(v.getL() != null){
            return minimum(v).getKey();
        }
        else {
            y = v.getP();
            while(y != null && v == y.getL()){
                v = y;
                y = v.getP();
            }
        }
        if(y == null) return 0; //controllo per nullpointerexception
        return y.getKey();
    }

}
