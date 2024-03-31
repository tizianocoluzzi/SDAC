#include "mat_sparsa_lista.h"
#include <stdlib.h>
#include <stdio.h>

//in teoria è andato daje roma daje
typedef struct elem {
	int i;
	int j;
	int x;
	struct elem *next;
} elem;

struct matrice_sparsa {
	int m;
	int n;
	elem* head;
};

void del_elem(matrice_sparsa* mat, int i, int j);
void elimina_scl(elem* mat);
void print_lineare(matrice_sparsa* mat);

void print_lineare(matrice_sparsa* mat){
	elem* c = mat->head;
	while(c != NULL){
		printf("%d->", c->x);
		c = c->next;
	}
	printf("\n");
}

matrice_sparsa* matrice_sparsa_new(int m, int n) {
	// la nuova matrice non ha elementi
	matrice_sparsa* mat = (matrice_sparsa*)  malloc(sizeof(matrice_sparsa));
	mat->m = m;
	mat->n = n;
	mat->head = NULL;
	return mat;
}


void elimina_scl(elem* mat){
	if(mat == NULL){return;}
	elimina_scl(mat->next);
	free(mat);

}

void matrice_sparsa_delete(matrice_sparsa* mat) {
	// TODO: Implement here
	elimina_scl(mat->head);
	free(mat);

}

int get_num_row(matrice_sparsa* mat) {
	if(mat!= NULL){
		return mat->m;
	}
	return 0;
}

int get_num_col(matrice_sparsa* mat) {
	if(mat!= NULL){
		return mat->n;
	}
	return 0;
}

void del_elem(matrice_sparsa* mat, int i, int j){
	elem* c = mat->head;
	elem* prec = NULL;
	while(c != NULL){
		if(c->i == i && c->j == j){
			if(prec == NULL){
				mat->head = c->next;
				free(c);
			}
			else{
				prec->next = c->next;
				free(c);
			}
			return;
		}
		prec = c;
		c = c->next;
	}
}

void mat_set(matrice_sparsa* mat, int i, int j, int x) {
	// TODO: Implement here
	//due operazioni creazione del blocco e modifica di uno esistente
	elem* c = mat->head;
	if(i >= mat->m || j >= mat->n) { printf("numero di righe o di colonne insufficiente\n"); return;}
	if(x == 0){del_elem(mat, i, j); return;} //se il valore è zero viene eliminato il blocco
	if(c == NULL || i < c->i || (i == c->i && j < c->j)){//inserimento in testa
		elem* nuovo = (elem*) malloc(sizeof(elem));
		nuovo->i = i;
		nuovo->j = j;
		nuovo->x = x;
		nuovo->next = c;
		mat->head = nuovo;
		return;
	}
	while(c!= NULL){
		if(c->i == i && c->j == j){
			//modifica del blocco
			c->x = x;
			return;
		}
		else if(c->next != NULL && (c->next->i > i || ( c->next->i == i && c->next->j > j)) ){
			//inserimento del blocco
			//printf("inserisco un nuovo blocco\n");
			elem* nuovo = (elem*) malloc(sizeof(elem));
			nuovo->i = i;
			nuovo->j = j;
			nuovo->x = x;
			nuovo->next = c->next;
			c->next = nuovo;
			return;
		}
		else if(c->next == NULL){
			//printf("inserimento in coda\n");
			elem* nuovo = (elem*) malloc(sizeof(elem));
			nuovo->i = i;
			nuovo->j = j;
			nuovo->x = x;
			nuovo->next = NULL;
			c->next = nuovo;
			return;
		}
		else{
			c = c->next;
		}
	}
}

int mat_get(matrice_sparsa* mat, int i, int j) {
	elem* c = mat->head;
	while(c != NULL){
		if(c->i == i && c->j == j)
			return c->x;
		c = c->next;
	}
	return 0;
}

void mat_print(matrice_sparsa* mat) {
	//TODO Implement here
	//printf("chiamata funzione mat_print\n");
	//elem* current = (elem*) malloc(sizeof(elem));
	elem* current = mat->head;
	printf("righe: %d  colonne: %d\n", mat->m, mat->n);
	for(int i = 0; i < mat->m; i++){
	    for(int j = 0; j < mat->n; j++){
			if(current != NULL && current->i == i && current ->j == j){
				printf(" %d ",current->x);
				
				current = current->next;
			}
			else
				printf(" 0 ");
	    }
	    printf("\n");
	}
	//free(current);
}
//Ritorna mat1+mat2 come una nuova matrice
matrice_sparsa* mat_add(matrice_sparsa* mat1, matrice_sparsa* mat2){
	mat_print(mat1);
	mat_print(mat2);
	print_lineare(mat1);
	print_lineare(mat2);
	if(mat1->m != mat2->m || mat1->n != mat2->n) {printf("errore di dimensione delle matrici"); return NULL;}
	matrice_sparsa* mat = matrice_sparsa_new(mat1->m, mat1->n);
	elem* c1 = mat1->head;
	elem* c2 = mat2->head;
	while(c1 != NULL || c2 != NULL){
		if(c1 != NULL && c2 != NULL){
			printf("%d  %d\n", c1->x, c2->x);
			if(c1->i == c2->i && c1->j == c2->j){
				mat_set(mat, c1->i , c1->j, c1->x + c2->x);
				c1 = c1->next;
				c2 = c2->next;
			}
			else if(c1->i <= c2->i && c1->j < c2->j){
				mat_set(mat, c1->i, c1->j, c1->x);
				c1 = c1->next;
			}
			else if(c1->i >= c2->i && c1->j > c2->j){
				mat_set(mat, c2->i, c2->j, c2->x);
				c2 = c2->next;
			}
		}
		else if(c1 != NULL){
			mat_set(mat, c1->i, c1->j, c1->x);
			c1 = c1->next;
		}
		else if(c2 != NULL){
			mat_set(mat, c2->i, c2->j, c2->x);
			c2 = c2->next;
		}
	}
	return mat;

}

//Ritorna mat^t come una nuova matrice
matrice_sparsa* mat_tra(matrice_sparsa* mat){
	matrice_sparsa* m = matrice_sparsa_new(mat->n, mat->m);
	//print_lineare(m);
	elem* c = mat->head;
	while(c != NULL){
		mat_set(m, c->j, c->i, c->x);
		c = c->next;
	}
	print_lineare(m);
	return m;
}

//Ritorna mat1*mat2 come una nuova matrice
matrice_sparsa* mat_mul(matrice_sparsa* mat1, matrice_sparsa* mat2){
	int ri = mat1->m;
	int col = mat2->n;
	if(mat1->n != mat2->m){
		printf("errore di dimensione delle matrici");
		return NULL;
	}
	matrice_sparsa* m = matrice_sparsa_new(ri, col);	
	for(int i = 0; i < ri; i++){
		for(int j = 0; j < col; j++){
			int prod = 0;
			for(int k = 0; k < mat2->m; k++){
				prod += mat_get(mat1, i, k) * mat_get(mat2, k, j);
			}
			mat_set(m, i, j, prod);
		}
	}

	return m;
}