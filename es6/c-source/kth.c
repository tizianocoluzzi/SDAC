#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "kth.h"

kth * kth_new(int k) {
	kth* kt = (kth*) malloc(sizeof(kth*));
	//stabilisco una size arbitraria a 100
	kt->max_heap = heap_new(MAX_HEAP,100);
	kt->min_heap = heap_new(MIN_HEAP,100);
	kt->k = k;
	return kt;
}
//la logica dell'insert:
//il massimo dei primi k elementi 
//è il k-esimo elemento

void kth_insert(kth * dd, int key) {
	if(dd->min_heap->used < dd->k){
		heap_add(dd->min_heap, key);
		heap_add(dd->max_heap, key);
	}
	else{
		heap_add(dd->max_heap, key);
		heap_poll(dd->max_heap);
		heap_add(dd->min_heap, key);
	}
	return;
}

int kth_get(kth * dd) {
	printf("k:%d\n", dd->k);
	// heap_print(dd->max_heap);
	// heap_print(dd->min_heap);
	if(dd->max_heap->used < dd->k){
		printf("non cè kth elemento\n");
		return 0;
	}
	return dd->max_heap->array[0]->key;
}

void kth_remove(kth * dd) {
	if(dd->max_heap->used >= dd->k){
		heap_poll(dd->max_heap);
		
	}
	return;
}

void kth_delete(kth * dd) {
	heap_delete(dd->max_heap);
	heap_delete(dd->min_heap);
	free(dd);
}