#include "labirinto.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
typedef struct {
    int n;
    int **matrix;
    int **marcata;
} labirinto_struct ;

labirinto* labirinto_new(int n) {
    labirinto_struct* lab = (labirinto_struct*) malloc(sizeof(labirinto_struct));
    lab->marcata = (int**) malloc(n*sizeof(int*));
    lab->matrix = (int**) malloc(n*sizeof(int*));
    lab->n = n;
    for(int i = 0; i < n; i++){
        lab->matrix[i] = (int*) malloc(n*sizeof(int));
        lab->marcata[i] = (int*) malloc(n*sizeof(int));
        for(int j = 0; j < n; j++){
            lab->marcata[i][j] = LABIRINTO_FALSE;
            lab->matrix[i][j] = LABIRINTO_VUOTA;
        }
    }
	return (labirinto*)lab;
}

void labirinto_delete(labirinto * lab) {
    labirinto_struct* del = (labirinto_struct*) lab;
    for(int i = 0; i < del->n; i++){
        free(del->matrix[i]);
        free(del->marcata[i]); 
    }
    free(del->marcata);
    free(del->matrix);
    free(del);
}

void labirinto_setpiena(labirinto * lab, int r, int c) {
    labirinto_struct* l = (labirinto_struct*) lab;
    l->matrix[r][c] = LABIRINTO_PIENA;
}

int labirinto_uscita(labirinto * lab, int r, int c) {
    labirinto_struct* l = (labirinto_struct*) lab;
    int n = l->n;
    if(r == n-1 && c == n-1) return 1; 
	return 0;
}

int labirinto_percorribile(labirinto * lab, int r, int c) {
    labirinto_struct* l = (labirinto_struct*) lab;
    if(l->matrix[r][c] == LABIRINTO_VUOTA) return 1; 
	return 0;
}

int labirinto_uscitaraggiungibileda(labirinto * lab, int r, int c) {


    //casi base: 1) la casella è l'uscita 2) è inammissibile 3) è muro 4) ci sono gia passato
    labirinto_struct* l = (labirinto_struct*) lab;
    int n = l->n;
    printf("cella: %d, %d\n", r, c);
    if(r < 0 || c < 0 || r > n-1 || c > n-1){printf("cella impossibile\n"); return 0;}
    if(l->marcata[r][c] == LABIRINTO_TRUE){ printf("cella marcata\n"); return 0;}
    
    l->marcata[r][c] = LABIRINTO_TRUE;
    
    if(!labirinto_percorribile(lab, r, c)) {printf("cella muro\n");return 0;}
    if(labirinto_uscita(lab, r, c)) {
        printf("uscita trovata\n");
        return 1;
    }
    //la condizione fondamentale sarebbe che non torna alla chiamante
    //utilzzo il marcata per decretare se ci sono gia passato ma non funziona
    //if(labirinto_uscitaraggiungibileda(lab, r+1, c) || labirinto_uscitaraggiungibileda(lab, r, c+1)){
    //condizioni adiacenti
    printf("ricorsione\n");
    int c1 = labirinto_uscitaraggiungibileda(lab, r-1, c);
    int c2 = labirinto_uscitaraggiungibileda(lab, r, c-1);
    int c3 = labirinto_uscitaraggiungibileda(lab, r+1, c);
    int c4 = labirinto_uscitaraggiungibileda(lab, r, c+1);
    if(c1 || c2 || c3 || c4) {
        return 1;
    }
    //dopo aver effettuato i controlli pongo false le celle che non conducono all'uscita
    l->marcata[r][c] = LABIRINTO_FALSE;
    return 0;
}

int labirinto_risolvibile(labirinto * lab) {
	return labirinto_uscitaraggiungibileda(lab, 0, 0);
}

void labirinto_tostring(labirinto * lab, char * buffer, int buffer_size) {
	labirinto_struct * ptr = (labirinto_struct *) lab;
        assert(buffer_size >= (ptr->n + 1) * ptr->n);
    buffer[0] = '\0';
    char *buffer_ptr = buffer;
    int i;
    for (i = 0; i < ptr->n; i++) {
        int j;
        for (j = 0; j < ptr->n; j++) {
            char c;
            if(ptr->matrix[i][j] == LABIRINTO_PIENA)
                c = '#';
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_FALSE)
                c = '.'; 
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_TRUE)
                c = '+'; 
            buffer_ptr[0] = c;
            buffer_ptr++;
        }
        buffer_ptr[0] = '\n';
        buffer_ptr++;
    }
    buffer_ptr[0] = '\0';

}
int marcata(labirinto* lab, int r, int c){
    labirinto_struct* l = (labirinto_struct*) lab;
    int n = l->n;
    if(r >= n || r<0 || c >= n || c<0) return 0;
    if(l->marcata[r][c] != LABIRINTO_FALSE) return 1;
    else return 0;
}