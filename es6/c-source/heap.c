#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


heap * heap_new(HEAP_TYPE is_min_heap, int capacity) {
	heap* h = (heap*) malloc(sizeof(heap));
	h->array = (heap_entry**) malloc(capacity*sizeof(heap_entry*));
	for(int i = 0; i < capacity; i++){
		h->array[i] = (heap_entry*) malloc(sizeof(heap_entry));
		h->array[i]->key = 0;
		h->array[i]->position = i;
	}
	h->size = capacity;
	h->used = 0;
	h->is_min_heap = is_min_heap; 
	return h;
}

HEAP_TYPE heap_type(heap * hh) {
	return hh->is_min_heap;
}

int heap_peek(heap * hh) {
	for(int i = 0; i < hh->used; i++){
		if(hh->array[i]->position == 0){
			return hh->array[i]->key;
		}
	}
	printf("non è stata trovata alcuna radice");
	return 0;
}

heap_entry * heap_add(heap * hh, int key) {
	if(hh->used >= hh->size){
		printf("l'heap è pieno");
		return NULL;
	}
	int used = hh->used;
	int idx;
	int p = parent(used);
	if(p == -1){
		hh->array[0]->key = key;
	}
	//printf("aggiungo %d il cui genitore è in pos:%d\n", key, p);
	if(hh->is_min_heap){
		idx = decrease_key(hh, hh->array[used], key);
	}
	else{
		idx = increase_key(hh, hh->array[used], key);
	}
	//heap_update_key(hh, hh->array[used-1], key);
	hh->used++;
	return hh->array[idx];
}

int get_key_entry(heap_entry * ee) {
	return ee->key;
}

int heap_size(heap * hh) {
	return hh->used;
}


//TODO non è esatta perche in realta non si assicura che finisca veramente 
//all'ultima posizione
int heap_poll(heap * hh) {
	int key = hh->array[0]->key;
	//printf("poll %d", key);
	int idx;
	if(hh->is_min_heap){
		idx = increase_key(hh, hh->array[0], MAX);
		if(idx < hh->used-1){
			swap_elements(hh, idx+1, idx);
			idx = idx+1;
			
		}
		hh->used--; 
	}
	else{
		idx = decrease_key(hh, hh->array[0], MIN);
		if(idx < hh->used-1){
			swap_elements(hh, idx+1, idx);
			idx = idx+1;
		}
		hh->used--; 
	}
	//riassegno la chiave perche è comodo poi per l'heapSort
	hh->array[idx]->key = key;
	return key;
}

void heap_delete(heap * hh) {
	for(int i = 0; i < hh->size; i++)
		free(hh->array[i]);
	free(hh->array);
	free(hh);
}

heap * array2heap(int * array, int size, HEAP_TYPE is_min_heap) {
	heap* h = heap_new(is_min_heap, size);
	for(int i = 0; i < size; i++){
		heap_add(h, array[i]);
	}
	return h;
}

void heap_print(heap * hh) {
	int n = hh->used;
	for(int i = 0; i < n; i++){
		printf(" %d", hh->array[i]->key);
	}
	printf("\n");
	return;
}

void heap_sort(int * array, int size) {
	heap* h = array2heap(array, size, MAX_HEAP);
	int used = h->used;
	while(h->used > 0){
		swap_elements(h, 0, h->used-1);
		h->used--;
		decrease_key(h, h->array[0], h->array[0]->key);
	}
	//elimino l'heap perchè l'ho usato solo come appoggio per ordinare l'array
	//cambiando i valori perde le proprieta di max_heap
	h->used = used;
	for(int i = 0; i < size; i++){
		array[i] = h->array[i]->key;
	}
	heap_delete(h);
	return;
}

void swap_elements(heap* hh, int i, int j){
	if(i <= hh->used && j < hh->used && i >= 0 && j >= 0){
		int app = hh->array[i]->key;
		hh->array[i]->key = hh->array[j]->key;
		hh->array[j]->key = app;
	}
	return;
}

int decrease_key(heap* hh, heap_entry *ee, int key){
	ee->key = key;
	int i = ee->position;
	if(hh->is_min_heap){
		int p = parent(i);
		while(i > 0 && hh->array[i]->key < hh->array[p]->key){
			//printf("nodo: %d-%d, parent:%d-%d\n", hh->array[i]->key, i, hh->array[p]->key, p);
			swap_elements(hh, i, p);
			i = p;
			p = parent(i);
		}
		return i;
	}
	int idx;
	int r = rigth(i); int l = left(i);
	while(i < hh->used && l<=hh->used ){
		if(hh->array[l]->key > key) idx = l;
		else idx = i;
		if(r < hh->used && hh->array[r]->key > hh->array[idx]->key) idx = r;
		if(idx == i) break;
		swap_elements(hh, i, idx);
		i = idx;
		l = left(i); r = rigth(i);
	}
	return i;
	
}
int increase_key(heap* hh, heap_entry *ee, int key){
	ee->key = key;
	int i = ee->position;
	if(!hh->is_min_heap){
		int p = parent(i);
		while(i > 0 && hh->array[i]->key > hh->array[p]->key){
			//printf("nodo: %d, parent:%d\n", hh->array[i]->key, hh->array[p]->key);
			swap_elements(hh, i, p);
			i = p;
			p = parent(i);
		}
		return i;
	}
	int idx;
	int r = rigth(i); int l = left(i);
	while(i < hh->used && r<=hh->used ){
		if(hh->array[l]->key < key) idx = l;
		else idx = i;
		if(r < hh->used && hh->array[r]->key < hh->array[idx]->key) idx = r;
		swap_elements(hh, i, idx);
		i = idx;
		l = left(i); r = rigth(i);
	}
	return i;
}

void heap_update_key(heap * hh, heap_entry * ee, int key) {
	if(key < ee->key){
		decrease_key(hh, ee,key);
	}
	else{
		increase_key(hh, ee, key);
	}
	return;        
}
//la formula dei figli e dei genitori è in realtà a/2 e a*2 e a*2+1
//considerando che gli indici partono da 1 allora uso le seguenti
int parent(int a){
	return (a+1)/2 -1 ;
}
int left(int a){
	return (a+1)*2 -1 ;
}
int rigth(int a){
	return (a+1)*2; //sarebbe +1 -1
}
