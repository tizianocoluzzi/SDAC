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

void DFS_visit(graph_node* gn){
    if(gn == NULL) return;
    if(gn->out_edges == NULL) return;
    if(gn->status == EXPLORED || gn->status == EXPLORING) return;
    linked_list_node* node = gn->out_edges->head;
    gn->status = EXPLORING;
    gn->timestamp = time++;
    while(node != NULL){
        graph_node* s = (graph_node*)node->value;
        if(s->status == UNEXPLORED){
            DFS_visit(s);
        }
        node = node->next;
    }
    gn->status = EXPLORED;
    gn->timestamp = time++; 
    // printf(format_string, gn->value);
    // printf("\n");
}
void DFS(graph * g) {
    if(g == NULL) return;
    if(g->nodes == NULL) return;
    linked_list_node* node = g->nodes->head;
    while(node != NULL){
        DFS_visit(((graph_node*)node->value));
        node = node->next;
    }
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

}

void strong_connected_components(graph  *g) {
    DFS(g);
    //TODO creare la DFS che crea gli alberi
    DFS_specialized(g);
}
