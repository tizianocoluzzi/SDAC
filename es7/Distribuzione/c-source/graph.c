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
	char str[3];
	while(fgets(str, 3, input)){
		//il problema è che se faccio la malloc non puntano allo stesso indirizzo
		//probabilmente devo verificare se il valore è gia presente
		//assumo quindi che il valore sia unico
		printf("%s", str);
	}
	return g;
}

void graph_print(graph* g) {
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

void graph_print_adj(graph* g) {
	//rappresentazione ad archi, brutale
	printf("rappresentazione ad archi non implementata\n");
}


int graph_n_con_comp(graph * g) {
	return 0;
}

linked_list* graph_get_con_comp(graph* g) {
	return NULL;
}
