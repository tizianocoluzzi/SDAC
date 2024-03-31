#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

// prototipi 
void launcher(int*, int);
int *randArray(int);
void printArray(int*, int);


//
void bubbleSort(int*, int);



int * randArray(int n) {
    srand(time(NULL));
    int *v = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++) v[i] = rand();
    return v;
}

void launcher(int *a, int n) {
    printArray(a, n);
    printf("Lancio il Bubble Sort... ");
    clock_t begin = clock();
    bubbleSort(a, n);
    clock_t end = clock();
    printf("fatto. Tempo: %g msec.\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    printArray(a, n);
    // t2-t1 è il tempo impiegato da bubbleSort
}

void printArray(int *a, int n) {
    printf("L'array ha %d elementi\n", n);
    for(int i = 0; i < n; i++) printf("array[%d] = %d\n", i, a[i]);
    printf("Fine array.\n");
}


int main(int argc, char *argv[]) {
    // test
    char* rnd = "rnd";
    for (int i = 0; i < argc; i++) printf("argomento n. %d è %s\n", i, argv[i]);
    //int v[8] = {64, 34, 25, 12, 22, 11, 90, 100};	
    if(argc >= 2 && strcmp(argv[1],rnd) == 0){
	printf("condizione verificata");
	int n = atoi(argv[2]);
	int* v = randArray(n);
	launcher(v, n);
	return 0;
    }
    int v[argc-1];
    for(int i = 0; i < argc-1; i++){
	v[i] = atoi(argv[i+1]);
	printf("argv: %s  v: %d\n", argv[i+1], v[i]);
    }
	
    
    launcher(v, argc-1);
    return 0;
}
