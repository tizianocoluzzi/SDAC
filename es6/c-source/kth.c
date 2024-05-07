#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "kth.h"

//utilizzo il max heap per tenere traccia dei primi k elementi
// il mi hepa per i restanti, in modo da avere sempre a portata di mano il kth
// e il k+1, cosi quando si fa il remove si prente la radice di min_heap
//si mette in max_heap

kth * kth_new(int k) {
	kth* kt = (kth*) malloc(sizeof(kth*));
	//stabilisco una size arbitraria a 100
	kt->max_heap = heap_new(MAX_HEAP,100);
	kt->min_heap = heap_new(MIN_HEAP,100);
	kt->k = k;
	return kt;
}

void kth_insert(kth * dd, int key) {
		//heap_add(dd->min_heap, key);
	if(dd->max_heap->used < dd->k){
		heap_add(dd->max_heap, key);
	}
	else{
		if(key < kth_get(dd)){
			//aggiungo la radice di max_heap in min_heap in modo da tenerne traccia
			int k = heap_poll(dd->max_heap);
			heap_add(dd->max_heap, key);
			heap_add(dd->min_heap, k);
		}
		else{
			heap_add(dd->min_heap, key);
		}
	}
	return;
}

int kth_get(kth * dd) {
	// heap_print(dd->max_heap);
	// heap_print(dd->min_heap);
	if(dd->max_heap->used < dd->k){
		printf("non cè kth elemento\n");
		return -1;
	}
	return dd->max_heap->array[0]->key;
}

void kth_remove(kth * dd) {
	if(dd->max_heap->used >= dd->k){
		heap_poll(dd->max_heap);
		if(dd->min_heap->used > 0){
			int j = heap_poll(dd->min_heap);
			heap_add(dd->max_heap, j);
		}
	}
	return;
}

void kth_delete(kth * dd) {
	heap_delete(dd->max_heap);
	heap_delete(dd->min_heap);
	free(dd);
}