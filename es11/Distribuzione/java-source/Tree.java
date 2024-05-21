public class Tree {

    private int key;
    private Tree left;
    private Tree right;

    public Tree(int key) {
        this.key = key;
    }

    public static Tree build_1() {
        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.left = n3;
        n6.right = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_2() {
        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.right = n3;
        n6.left = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_3() {
        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);

        n6.left = n3;

        n3.left = n1;
        n3.right = n5;

        n5.right = n12;

        return n6;
    }

    private boolean isBSTRec(Tree c){
        if(c == null) return true; 
        if(c.left == null && c.right == null) return true;
        if(c.left == null && c.right.key < key ) return false;
        else if(c.right == null && c.left.key > key) return false;
        if(c.left.key > c.key || c.right.key < c.key) return false;
        else return isBSTRec(c.left) && isBSTRec(c.right);
    }

    public boolean isBST() {
        return isBSTRec(this);
    }

    private int max(int a, int b){
        if(a < b) return b;
        else return a;

    }

    private int isBalancedRec(Tree c){
        if(c == null) return 0;
        if(c.left == null && c.right == null) return 1;
        int isL = isBalancedRec(c.left);
        int isR = isBalancedRec(c.right);
        if(isL == -1 || isR == -1) return -1;
        if(Math.abs(isL - isR) <= 1) return 1 + max(isL, isR);
        return -1;
    }

    public boolean isBalanced() {
        if(isBalancedRec(this) == -1) return false;
        return true;
    }

    public boolean isAVL() {
        return true;
    }

}
