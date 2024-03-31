#include <stdio.h>
#include <stdlib.h>

int saltacasella(int** mat, int i, int j, int n, int N);
static int driver(int** mat, int N);
static void stampamatrice(int** mat, int N);

long Cont = 0;

int saltacasella(int** mat, int i, int j, int n, int N) {
    //printf("entrato nel saltacasella\n");
    if(i < 0 || j < 0 || i >= N || j >= N) return 3; //caso caselle inammissibili
    if(mat[i][j] != 0) return 3; //caso casella gia piena;
    if(n == N*N) {
        mat[i][j] = n;
        return 0;}
    int m = n+1;
    int ind1[8] = {3, 2, 0, -2, -3, -2, 0, 2};
    int ind2[8] = {0, 2, 3, 2, 0, -2, -3, -2};
    mat[i][j] = n;
    for(int h = 0; h < 8; h++){
        if(saltacasella(mat, i+ind1[h], j +ind2[h], m, N) == 0) return 0;
    }
    mat[i][j] = 0;
    return 3; /* no soluzione */
}


static int driver(int** mat, int N) {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) 
            if(saltacasella(mat, i, j, 1, N) == 0) return 0;
    return(3);
}

static void stampamatrice(int** mat, int N) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) printf("%4d", mat[i][j]);
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("./saltacasella <size>");
        exit(3);
    }
    int N = atoi(argv[1]);
    int **mat = malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++) mat[i] = calloc(N, sizeof(int));
    if(driver(mat, N) == 0)
        stampamatrice(mat, N);
    else
        printf("\nnon trovato\n");
    return 0;
}