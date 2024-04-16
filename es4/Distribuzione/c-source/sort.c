#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "sort.h"

void merge(array* a, int i, int m ,int f){
    array* app = (array*) malloc(sizeof(array));
    app->size = f-i+1;
    app->arr = (int*) malloc(app->size*sizeof(int));
    int j = 0;
    int h = i;
    int k = m+1;
    while(h <= m && k <= f){
        if(a->arr[h] <= a->arr[k]){
            app->arr[j] = a->arr[h];
            h++;
            j++;
        }
        else{
            app->arr[j] = a->arr[k];
            k++;
            j++;
        }
    } 
    while(h <= m){
        app->arr[j] = a->arr[h];
        h++;
        j++;
    }
    while(k <= f){
        app->arr[j] = a->arr[k];
        k++;
        j++;
    }
    for(int c = 0; c < app->size; c++){
        a->arr[i+c] = app->arr[c];
    }

}

void mergeSort_aux(array* a, int i, int f){
    if(i == f){
        return;
    }
    else{
        mergeSort_aux(a, i, (i+f)/2);
        mergeSort_aux(a, (i+f)/2 + 1, f);
        merge(a, i, (i+f)/2, f);
    }
}

void mergeSort(array *a) {
    mergeSort_aux(a, 0, a->size-1);
    return;
}



void heapSort(array *a) {
    //non implemento l'heap sort poichè presente nelle successive esercitazioni
}

void infila(array* a, int elem, int i){
    int j = i-1;
    while( j >= 0){
        if(a->arr[j] > elem){
           int app = a->arr[j];
           a->arr[j] = elem;
           a->arr[j+1] = app; 
           j--;
       } 
       else{return;}
    }
}

void insertionSort(array *a) {
    for(int i = 1; i < a->size; i++){
        infila(a, a->arr[i], i);
    }
    return;
}

int cercaMin(array* a, int i){
    int minidx = i;
    for(int j = i; j < a->size; j++){
        if(a->arr[j] < a->arr[minidx]) minidx = j;
    }
    return minidx;
}

void selectionSort(array *a) {
    for(int i = 0; i < a->size; i++){
        int idx = cercaMin(a, i);
        int app = a->arr[i];
        a->arr[i] = a->arr[idx];
        a->arr[idx] = app;
    }
    return;
}



void quickSort_aux(int* a, int s) {
    //TODO migliorare l'efficienza che a quanto pare non va molto bene
    if(s <= 1){
        return;
    }
    else{
        int d_size = 0;
        int s_size = 0;
        int h =0;
        int k = 0;
        int* sx = (int*) malloc(s*sizeof(int));
        int* dx = (int*) malloc(s*sizeof(int));
        int pivot = a[0];
        for(int i = 1; i < s; i++){
            if(a[i] >= a[0]){
                d_size += 1;
                dx[h] = a[i];
                h++;
            }
            else{
                s_size += 1;
                sx[k] = a[i];
                k++;
            }
        }
        quickSort_aux(sx, s_size);
        quickSort_aux(dx, d_size);
        for(int i = 0; i <s_size; i++){
            a[i] = sx[i];
        }
        a[s_size] = pivot;
        for(int i = s_size+1; i < s; i++){
            a[i] = dx[i - s_size -1];
        }
        free(sx);
        free(dx);
    }
    return;
}

void quickSort(array *a){
    quickSort_aux(a->arr, a->size);
}

void swap(int* a, int j, int k){
    int app = a[j];
    a[j] = a[k];
    a[k] = app;
}

void radix_aux(int* arr, int s, int k, int i, int j){
    //caso base
    if(i >= j || k > 32) return;
    int ptr = i;
    int app1;
    int app2;
    printf("\nchiamata\n");
    for(int h = i; h <= j; h++){
        //le due cifre binarie piu significative
        app1 = 1 & (arr[ptr] >> ( 8*sizeof(int) - k));;
        app2 = 1 & (arr[h] >> ( 8*sizeof(int) - k));
        printf("%d %d ", arr[h], app2);
        if(app1 == 1 && app2 == 0){
            swap(arr, ptr, h);
            ptr++;
        }
        else if(app1 == 0) ptr++;
    }
    radix_aux(arr, s, k+1, i, ptr -1);
    radix_aux(arr, s, k+1, ptr, j);
}

void radixSort(array *a) {
    //problema principale è la conversione di un numero in binario
    //per 32 volte devo stabilire se la cifra data dall'espressione 
    //1 & (a >> ( 8*sizeof(int) - i)) è unno o zero, metterla nella porzione corretta di array
    //reiterare sulla successiva
    //(maggiore è i meno la civra è significativa)
    int * arr = a->arr;
    int s = a->size;
    radix_aux(arr, s, 1, 0, s-1);
    fprintf(stdout, "radixSort currently not implemented.\n");
    return;
}

int max(int* a, int s){
    int max = 0;
    for(int i = 0; i < s; i++){
        if(a[i] > max) max = a[i];
    }
    return max;
}

void bubblesort(int* a, int idx){
    for(int i = 0; i < idx; i++){
        for(int j = 0; j < idx - 1; j++){
            if(a[j] >= a[j+1]){
                swap(a, i, j);
            }
        }
    }
}

void bucketSort(array *a) {
    //fprintf(stdout, "bucketSort currently not implemented.\n");
    //Dobbiamo assumere che l'input sia uniformemente distribuito
    int s = a->size;
    int* arr  = a->arr; //dato che ha reso piu veloce il quickSort ci provo anche qui 
    float norma = 0;
    //inizializzo l'array di bucket
    int** bckts = (int**) malloc(10*sizeof(int*));
    for(int i = 0; i <10; i++){
        bckts[i] = (int*) calloc(s,sizeof(int));
    }
    // for(int i = 0; i < s; i++){
    //     norma += arr[i] * arr[i];
    // }
    norma = max(arr, s) + 1;
    //printf("norma:%d\n",(int) norma);
    int* idx = (int*) calloc(10,sizeof(int)); //array per tenere traccia dell'andamento degli indici
    for(int i = 0; i < s; i++){
        int index = (int) (((float) (arr[i] / norma)) * 10);
        //printf("inserisco %d normalizzato %f all indice %d",arr[i], arr[i]/norma,index);
        bckts[index][idx[index]] = arr[i];
        idx[index]++;
        //printf(" indice aggiornato:%d\n", idx[index]);
    }
    for(int i = 0; i < 10; i++){
        //utilizzo quickSort aux solo perche è gia definita per int* e non mi va di scriverne un altra
        //idealmente sarebbe da utilizzare insertionSort 
        //printf("riallocato vettore %d, %d\n", i, idx[i]);
        //bckts[i] = (int*) realloc(bckts[i], idx[i]);
        // for(int j = 0; j < idx[i]; j++){
        //     printf("%d ", bckts[i][j]);
        // }
        // printf("\n");
        quickSort_aux(bckts[i], idx[i]);
    }
    int sum = 0;
    for(int i = 0; i < 10; i++){
        for(int j  = 0; j < idx[i]; j++){
            arr[sum] = bckts[i][j];
            sum++;
        }
    }

    return;
}

