#include <stdio.h>

#include "graph.h"
#include "linked_list.h"
#include "graph_services.h"

int time = 0; 

void clean(graph *g){
    //resetta l'albero e la variabile time
    if(g == NULL) return;
    if(g->nodes == NULL) return;
    linked_list_node* node = g->nodes->head;
    time = 0;
    while(node != NULL){
        ((graph_node*)node->value)->timestamp = 0;
        ((graph_node*)node->value)->status = UNEXPLORED;
        node = node->next;
    }
}

void DFS_print(graph_node* gn, char*format_string){
    if(gn == NULL) return;
    if(gn->out_edges == NULL) return;
    if(gn->status == EXPLORED || gn->status == EXPLORING) return;
    linked_list_node* node = gn->out_edges->head;
    gn->status = EXPLORING;
    gn->timestamp = time++;
    while(node != NULL){
        graph_node* s = (graph_node*)node->value;
        printf(format_string, gn->value);
        printf(" ");
        if(s->status == UNEXPLORED){
            printf(format_string, s->value);
            printf(" ARCO TREE\n");
            DFS_print(s, format_string);
        }
        else if(s->status == EXPLORING){
            printf(format_string, s->value);
            printf(" ARCO BACK  \n");
        }
        else if(s->status == EXPLORED){
            if(s->timestamp > gn->timestamp){
                printf(format_string, s->value);
                printf(" ARCO FORWARD  \n");
            }
            else{
                printf(format_string, s->value);
                printf(" ARCO CROSS  \n");
            }
        }
        node = node->next;
    }
    gn->status = EXPLORED;
    gn->timestamp = time++; 
    // printf(format_string, gn->value);
    // printf("\n");
}
//pila per l'ordinamento topologico
linked_list* pila;
//controllare che sia aciclico
int is_DAG;
void DFS_visit(graph_node* gn){
    if(gn == NULL) return;
    if(gn->status == EXPLORING)return;
    if(gn->status == EXPLORED)return;
    if(gn->out_edges == NULL) return;
    //creo la pila per ordinare 
    linked_list_node* node = gn->out_edges->head;
    gn->status = EXPLORING;
    gn->timestamp = time++;
    while(node != NULL){
        graph_node* s = (graph_node*)node->value;
        if(s->status == UNEXPLORED){
            DFS_visit(s);
        }
        if(s->status == EXPLORING) is_DAG = 1;
        node = node->next;
    }
    gn->status = EXPLORED;
    gn->timestamp = time++;
    linked_list_add(pila, 0,gn); 
    // printf(format_string, gn->value);
    // printf("\n");
}
void DFS(graph * g) {
    if(g == NULL) return;
    if(g->nodes == NULL) return;
    linked_list_node* node = g->nodes->head;
    //inizializzo la pila per mettere in ordine di visita
    pila = linked_list_new();
    is_DAG = 0;
    while(node != NULL){
        DFS_visit(((graph_node*)node->value));
        node = node->next;
    }
}

//il valore intero ritorna il numero dei back arc incontrati nella visita
int DFS_visit_specialized(graph_node* gn){
    if(gn == NULL) return 0;
    if(gn->in_edges == NULL) return 0;
    if(gn->status == EXPLORED) return 0; 
    if(gn->status == EXPLORING) return 1; //tiene conto dei back arc
    //creo la pila per ordinare 
    //pila = linked_list_new();
    int ret = 0;
    linked_list_node* node = gn->in_edges->head;
    gn->status = EXPLORING;
    gn->timestamp = time++;
    while(node != NULL){
        graph_node* s = (graph_node*)node->value;
        if(s->status == UNEXPLORED){
            ret += DFS_visit_specialized(s);
            printf("%s ", (char*)s->value);
        }
        node = node->next;
    }
    gn->status = EXPLORED;
    gn->timestamp = time++;
    return ret;
    //linked_list_add(pila, 0,gn); 
    // printf(format_string, gn->value);
    // printf("\n");
}
void DFS_specialized(graph * g, linked_list* pila) {
    if(g == NULL) return;
    if(g->nodes == NULL) return;
    linked_list_node* node = pila->head;
    while(node != NULL){
        if(((graph_node*)node->value)->status == UNEXPLORED){
            printf("%s ", (char*)((graph_node*)node->value)->value);
            DFS_visit_specialized(((graph_node*)node->value));
            printf("\n");
        }
        node = node->next;
    }
    return;
}

void sweep(graph * g, char * format_string) {
    if(g == NULL) return;
    if(g->nodes == NULL) return;
    linked_list_node* node = g->nodes->head;
    while(node != NULL){
        DFS_print(((graph_node*)node->value), format_string);
        node = node->next;
    }
    //pulisco l'albero
    clean(g);
}


void topological_sort(graph * g){
    DFS(g);
    if(is_DAG == 1){
        printf("fallito poichè presente ciclo\n");
        clean(g);
        return;
    }
    linked_list_node* node = pila->head;
    while(node != NULL){
        printf("%s\n", (char*)((graph_node*)node->value)->value);
        node = node->next;
    }
    clean(g);
}

void strong_connected_components(graph  *g) {
    DFS(g);
    //pulisco per fare in modo che la seconda DFS abbia successo
    clean(g);
    //TODO creare la DFS che crea gli alberi
    DFS_specialized(g, pila);
    
}
