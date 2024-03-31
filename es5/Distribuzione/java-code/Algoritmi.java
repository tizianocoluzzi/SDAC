/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.*;
/**
 *
 * @author silvia
 */
public class Algoritmi {
    public static void swap(float[] a, int i, int j){
        float app = a[i];
        a[i] = a[j];
        a[j] = app;
    }
    
     
    public static void permuta_negativi_positivi(float [] a){
        //System.out.println("Metodo non ancora implementato... Risultato non disponibile");
        int pos = 0;
        int neg = 0;
        for(int i = 0; i < a.length; i++){
            if(a[pos] >= 0){
                if(a[neg] < 0){
                    swap(a, pos, neg);
                    pos++;
                    neg++;
                }
                else{
                    neg++;
                }
            }
            else{
                if(pos == neg){
                    pos++;
                    neg++;
                }         
                else{
                    pos++;
                }           
            }
        }
        return;
}
    
    public static void swap_char(char[] a, int i, int j){
        char app = a[i];
        a[i] = a[j];
        a[j] = app;
    }

    public static void bandiera(char[] a){
        //System.out.println("Metodo non ancora implementato... Risultato non disponibile");
        int h = 0;
        int k = 0;
        for(int i = 0; i < a.length; i++){
            if(a[h] == 'v'){
                swap_char(a, h, k);
                h++;
                k++;
            }
            else{
                h++;
            }
        }
        h = 0;
        k = 0;
        Driver.stampaArray(a);
        System.out.println("");
        for(int i = 0; i < a.length; i++){
            if(a[h] == 'v' && a[k] == 'v') {
                h++; k++;
            }
            else if(a[h] == 'b' && a[k] == 'r'){
                swap_char(a, h, k);
                h++;
                k++;
            }
            else{
                h++;
            }
        }
        return;
    }
    
    public static boolean isOk(int[][] m, int i, int j){
        if(i < m.length -1 ){
            for(int h = i+1; h < m.length; h++){
                if(m[h][j] == m[i][j]) return false;
            }
        }
        if(j < m.length -1){
            for(int k = j+1; k < m.length; k++){
                if(m[i][k] == m[i][j]) return false;
            }
        }
        return true;
    }
       
    public static boolean isQuadratoLatino(int[][] m){
        //System.out.println("Metodo non ancora implementato... Risultato non disponibile");
        for(int i = 0; i < m.length; i++){
            for(int j = 0; j < m[i].length; j++){
                if(!isOk(m, i, j)){
                    return false;
                }
            }
        }
        return true;
    }

    public static int partition(float[] a, int i, int j){
        //il pivot è l'ultimo elemento
        int k = i;
        for(int idx = i; idx < j; idx++){
            if(a[idx] < a[j]){
                swap(a, idx, k);
                k++;
            }
        }
        swap(a, k, j);
        return k;
    }
    
    public static void primiKmin_app(float[] a, int k, int i, int j){
        if(j <= i || k < 0){
            return;
        }
        int p = partition(a, i, j);
        //non metto un controllo perche c'è come caso base
        //il k-p+1 è un quanti elementi ci sono ancora da cercare?
            primiKmin_app(a, k-p+1, i, p-1);
            primiKmin_app(a, k-p+1, p+1, j);
        return;

    }
    public static void primiKMin(float[] a, int k){
        primiKmin_app(a, k, 0, a.length - 1);
        if(k >= a.length){
            k = a.length;
            System.out.println("k>=n cmoprende tutti gli elementi del vettore");
        }
        for(int i = 0; i < k; i++){
            System.out.print(a[i] + " ");
        }
        System.out.println("");
        return;
    }
    
}
