#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
//TODO completare la parte di remove edge e continuare con i task successivi

typedef enum {UNEXPLORED, EXPLORED, EXPLORING} STATUS;



struct graph_node{
    void * value;
    linked_list * out_edges;

    // keep track status
    STATUS state;
    int timestamp;
};

struct graph{
    linked_list * nodes;
};

graph * graph_new() {
	graph* g = (graph*) malloc(sizeof(graph));
	g->nodes = linked_list_new();
	return g;
}

linked_list * graph_get_nodes(graph * g) {
	return g->nodes;
}

linked_list * graph_get_neighbors(graph * g, graph_node * n) {
	//TODO inserire controllo che il nodo apparenga al grafo
	return n->out_edges;
}

graph_node * graph_add_node(graph * g, void * value) {
	graph_node* n = (graph_node*) malloc(sizeof(graph_node));
	n->value = value;
	n->out_edges = linked_list_new();
	n->state = UNEXPLORED;
	n->timestamp = 0;
	linked_list_add(g->nodes, n);
	return n;
}

void graph_add_edge(graph * g, graph_node * v1, graph_node * v2) {
	//TODO aggiungere controllo esistenza 
	if(v1 == NULL || v2 == NULL) return;
	if(v1->out_edges == NULL || v2->out_edges == NULL) return;
    linked_list_add(v1->out_edges, v2);
	linked_list_add(v2->out_edges, v1);
	return;
}

void * graph_get_node_value(graph_node * n) {
	if(n == NULL) return NULL;
	return n->value;
}
//sto praticamente scansionando le cose sbagliate
void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {
	if (v1 == NULL || v2 == NULL || g== NULL) return;
	if (v1->out_edges == NULL || v2->out_edges == NULL) return;
	//if (v1->out_edges->head == NULL || v2->out_edges->head == NULL) return;
	linked_list_node* n = v1->out_edges->tail;
	int i = 0;
	while(n != NULL && i < v1->out_edges->size){
		//printf(" scansiono: %c\n", *(char*)((graph_node*)(n->value))->value);
		if(n->value == v2){
			//printf(" trovato match\n");
			linked_list_remove_last(v1->out_edges);
			//return;
		}
		else{
			void* app = n->value;
			linked_list_add_on_top(v1->out_edges, app);
			linked_list_remove_last(v1->out_edges);
		}
		n = v1->out_edges->tail;
		++i;
	}
	i = 0;
	n = v2->out_edges->tail;
	while(n != NULL && i < v2->out_edges->size){
		//printf("  scansiono: %c\n", *(char*)((graph_node*)(n->value))->value);
		if(n->value == v1){
			//printf("  trovato match\n");
			linked_list_remove_last(v2->out_edges);
			//return;
		}
		else{
			void* app = n->value;
			linked_list_add_on_top(v2->out_edges, app);
			linked_list_remove_last(v2->out_edges);
		}
		n = v2->out_edges->tail;
		++i;
	}
	return;
}

void graph_remove_node(graph* g, graph_node* v) {
	if(g == NULL|| v == NULL) return;
	if(g->nodes == NULL) return;
	linked_list_node* a = g->nodes->head;
	while(a != NULL){
		//printf("scansiono: %c\n", *(char*)((graph_node*)a->value)->value);
		graph_remove_edge(g, v, (graph_node*)a->value);
		a = a->next;
	}
	a = g->nodes->tail;
	while(a != NULL){
		if(v == (graph_node*)a->value){
			linked_list_remove_last(g->nodes);
			return;
		}
		else{
			void* value = a->value;
			linked_list_remove_last(g->nodes);
			linked_list_add_on_top(g->nodes, value);
		}
		a = g->nodes->tail;
	} 
	free(v->out_edges);
	v->value = 0;
	free(v);
}

void graph_delete(graph * g) {
	linked_list_delete(g->nodes);
	free(g);
}

graph* graph_read_ff(FILE* input) {
	graph * g = graph_new();
	graph_node** arr;
	int n;
	int m;
	fscanf(input,"%d%d\n", &n, &m);
	printf("nodi: %d  archi: %d\n", n, m);
	//creo n nodi
	arr = (graph_node**) malloc(n*sizeof(graph_node*));
	for(int i = 0; i < n; i++){
		int *j =(int*) malloc(sizeof(int));
		*j = i + 49;
		arr[i] = graph_add_node(g, (void*) j);
	}
	int n1;
	int n2;
	for(int i = 0; i < m; i++){
		fscanf(input, "%d%d", &n1, &n2);
		graph_add_edge(g, arr[n1-1], arr[n2-1]);
	}
	return g;
}

void graph_print(graph* g) {
	if(g != NULL && g->nodes != NULL){
		linked_list_node* a = g->nodes->head;
		while(a != NULL){
			if(a->value != NULL && ((graph_node*)a->value)->out_edges != NULL){
				linked_list_node* b = ((graph_node*)a->value)->out_edges->head;
				while(b != NULL){
					graph_node* node = (graph_node*) b->value;
					if(node->state == EXPLORED){}
					else {
						printf("%c %c\n", *(char*)graph_get_node_value((graph_node*)a->value), *(char*)graph_get_node_value((graph_node*)b->value));
					}
					//node->state = EXPLORED;
					b = b->next;
				}
				((graph_node*)(a->value))->state = EXPLORED;
			}
			a = a->next;
		}
		a = g->nodes->head;
		//resetto tutto a UNEXPLRED
		while(a != NULL){
			((graph_node*)(a->value))->state = UNEXPLORED;
			a = a->next;
		}
	}
}

void graph_print_adj(graph* g) {
	if(g != NULL && g->nodes != NULL){
		linked_list_node* a = g->nodes->head;
		while(a != NULL){
			if(a->value != NULL && ((graph_node*)a->value)->out_edges != NULL){
				linked_list_node* b = ((graph_node*)a->value)->out_edges->head;
				printf("%c:\n", *(char*)graph_get_node_value((graph_node*)a->value));
				while(b != NULL){
					graph_node* node = (graph_node*) b->value;
					if(node->state == EXPLORED){}
					else 
						printf(" %c\n", *(char*)graph_get_node_value((graph_node*)b->value));
					//node->state = EXPLORED;
					b = b->next;
				}
			}
			a = a->next;
		}
	}
}

// per resettare l'albero ai valori di default, probabilmente è concettualmente sbagliato

void reset(graph* g){
	if(g->nodes != NULL) return;
	linked_list_node* n = g->nodes->head;
	while(n != NULL){
		((graph_node*)n->value)->state = UNEXPLORED;
		((graph_node*)n->value)->timestamp = 0;
		n = n->next;
	}
}

int DFS_n_comp(graph* g, graph_node *gn){
	//printf("esploro: %c\n", *(char*)gn->value);
	if(gn->state == EXPLORED) return 0;
	if(gn->state == EXPLORING) return 0;
	gn->state = EXPLORING;
	if(gn->out_edges != NULL){
		linked_list_node* n = gn->out_edges->head;
		while(n != NULL){
			DFS_n_comp(g, (graph_node*)n->value);
			n = n->next;
		}
	}
	gn->state = EXPLORED;
	return 1;
}

int graph_n_con_comp(graph * g) {
	int k = 0;
	if(g != NULL && g->nodes != NULL){
		linked_list_node* n = g->nodes->head;
		while(n != NULL){
			graph_node* gn = (graph_node*)(n->value);
			k+= DFS_n_comp(g, gn);
			n = n->next;
		}
	}
	return k;
}



//impostare un timestamp diverso ogni volta che si incontra una nuova componente
//glob è il conto di quante componenti connnesse abbiamo
//se t è diverso da zero significa che la funzione è stat chiamata da un nodo che aveva un timestamp pari a t

//TODO N.B. la struttura è similie a quella scritta al momento ma avevo mal interpretato l'output
//modifche da fare:
//                  la funzione DFS_get_con_comp deve ritornare un albero
//				 	la funzione deve creare mano mano l'albero, quindi va passato come parametro
//					se non esiste lo crea e lo passa ai nodi connessi
void DFS_get_con_comp(graph* g, graph_node* gn, int t, int glob){
	if(gn->state == EXPLORED) return;
	if(gn->state == EXPLORING) return;
	gn->state = EXPLORING;
	if(gn->timestamp == 0){
		if(t == 0){
			gn->timestamp = glob;
			glob++;
		}
		else{
			gn->timestamp = t;
		}
		if(gn->out_edges != NULL){
			linked_list_node* n = gn->out_edges->head;
			while(n != NULL){
				DFS_get_con_comp(g, (graph_node*)n->value, gn->timestamp, glob);
				n = n->next;
			}
		}
	} 
	gn->state = EXPLORED;
	return;
	
}

linked_list* graph_get_con_comp(graph* g) {
	linked_list* ll = linked_list_new();
	int num = graph_n_con_comp(g);
	linked_list** l = (linked_list**) calloc(num, sizeof(linked_list*));
	reset(g); //reset del grafo in modo da esssere sicuro che sia impostato ai valori di default
	if(g != NULL && g->nodes != NULL){
		linked_list_node* n = g->nodes->head;
		while(n != NULL){
			graph_node* gn = (graph_node*)(n->value);
			DFS_get_con_comp(g, gn, 0, 1);
			n = n->next;
		}
		n = g->nodes->head;
		while(n != NULL){
			graph_node* gn = (graph_node*)(n->value);
			linked_list_add(l[gn->timestamp-1], gn->value);
			n = n->next;
		}
	}
	return NULL;
}
