import java.util.*;
import java.util.concurrent.*;


public class GraphServices {
    
    public static <V> void clear(Graph<V> g){
        Collection<Node<V>> nodes = g.getNodes();
        Iterator<Node<V>> i = nodes.iterator();
        while(i.hasNext()){
            Node<V> a = i.next();
            a.state = Node.Status.UNEXPLORED;
        }
    }

    public static <V> void bfs_aux(Graph<V> g, Node<V> n){
        //effettivamente implemento la bfs qui nel caso in cui la bfs
        //debba essere iterata su tutti i nodi
        n.state = Node.Status.EXPLORING;
        System.out.println(n);
        Queue<Node<V>> q = new ConcurrentLinkedQueue<Node<V>>();
        q.add(n);
        while(!q.isEmpty()){
            Node<V> u = q.poll();
            Collection<Edge<V>> neigh = g.getOutEdges(u);
            Iterator<Edge<V>> i = neigh.iterator();
            while(i.hasNext()){
                Edge<V> e = i.next();
                Node<V> v = e.getTarget();
                if(v.state == Node.Status.UNEXPLORED){
                    System.out.println(v);
                    v.state = Node.Status.EXPLORING;
                    q.add(v);
                }
            }
            u.state = Node.Status.EXPLORED;
        }
    }
    public static <V> void bfs(Graph<V> g) {
        Collection<Node<V>> nodes = g.getNodes();
        Iterator<Node<V>> i = nodes.iterator();
        while(i.hasNext()){
            Node<V> n = i.next();
            clear(g);
            System.out.println();
            if(n.state == Node.Status.UNEXPLORED){ 
               bfs_aux(g, n);
            }
        }
    }

    public static <V> void init_sorg(Graph<V> g, Node<V> s){
        Collection<Node<V>> nodes = g.getNodes();
        Iterator<Node<V>> i = nodes.iterator();
        while(i.hasNext()){
            Node<V> n = i.next();
            if(n != s){
                n.dist = 2147483647;
            }
        } 
        s.dist = 0;
    }

    public static <V> void relax(Graph<V> g, Node<V> s, Node<V> d){
        Collection<Edge<V>> out = g.getOutEdges(s);
        Iterator<Edge<V>> it = out.iterator();
        Edge<V> n;
        int w = -1;
        while(it.hasNext()){
            n = it.next();
            if(n.getTarget().equals(d) && n.getSource().equals(s)){
                //System.out.println("arco trovato");
                w = n.getWeight();
                break;
            }
        }
        if(w == -1) return;
        //System.out.println("arco: " + s + " " + d + " " + w);
        if(d.dist == -1){
            d.dist = s.dist + w;
        }
        else if(d.dist > s.dist + w){
            d.dist = s.dist + w;
        }
        //System.out.println(d.dist);
    }

    public static <V> Node<V> search(Graph<V> g, V s){
        Iterator<Node<V>> i = g.getNodes().iterator();
        while(i.hasNext()){
            Node<V> n = i.next();
            if(s == n.getValue()){
                return n;
            }
        }
        return null;
    }
    public static <V> int dijkstra(Graph<V> g, Node<V> s, Node<V> d){
        init_sorg(g, s);
        MinHeap<V> h = new MinHeap<V>();
        Iterator<Node<V>> i = g.getNodes().iterator();
        while(i.hasNext()){
            Node<V> n = i.next();
            h.insert(n.dist, n.getValue());
        }
        while(!h.isEmpty()){
            HeapEntry<V> e = h.removeMin();
            V val = e.getValue();
            Node<V> node = search(g, val);
            Iterator<Edge<V>> it = g.getOutEdges(node).iterator();
            while(it.hasNext()){
                Node<V> v = it.next().getTarget();
                relax(g, node, v);
                HeapEntry<V> en = h.get(v.getValue());
                if(en != null) h.replaceKey(en, v.dist);
            }
        }
        return d.dist;
    }

    public static <V> void sssp(Graph<V> g, Node<V> source) {
        Collection<Node<V>> nodes = g.getNodes();
        Iterator<Node<V>> i = nodes.iterator();
        while(i.hasNext()){
            Node<V> n = i.next();
            if(n != source){
                int dist = dijkstra(g, source, n);
                if(dist == 2147483647){
                    System.out.println(""+n+" infinito");
                }
                else{
                    System.out.println("" + n + " " + dist);
                }
            }
        } 
    }
    
    public static <V> void mst(Graph<V> G) {
        //creo le partizioni
        Partition<V> p = new Partition<V>(G.getNodes());
        Iterator<Edge<V>> it_edge = G.getEdges().iterator();
        ArrayList<Edge<V>> l = new ArrayList<Edge<V>>();
        while(it_edge.hasNext()){
            Edge<V> n = it_edge.next();
            l.add(n);
        }
        System.out.println();
        l.sort(new Comparator<Edge<V>>(){
            public int compare(Edge<V> o1, Edge<V> o2) {
                if(o1.getWeight() - o2.getWeight() == 0) return 0;
                if(o1.getWeight() - o2.getWeight() > 0) return 1;
                else return -1;
            }  
        });
        Iterator<Edge<V>> it = l.iterator();
        while(it.hasNext()){
            Edge<V> e = it.next();
            int keyS = e.getSource().map;
            int keyT = e.getTarget().map;
            
            //System.out.println(p.find(keyS).toString() + p.find(keyT).toString());
            if(!p.find(keyS).equals(p.find(keyT))){
                System.out.println(e.toString());
                p.union(keyS, keyT);
            }
        }
    }
}
