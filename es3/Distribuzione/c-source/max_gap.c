#include <assert.h>
#include <stdio.h>

#include "max_gap.h"

int maxGap(int * array, int start, int end) {
	//printf("%d %d %d\n", start, end/2, end);
	// TODO: Da completare
	if(start == end){
		//printf("ritornato 0\n");
		return 0;
	}
	else if(end - start <= 1){
		//se sono adiacenti
		//printf("trovata adiacenza %d %d\n", start, end);
		return array[end] - array[start];
	}
	else{
		int maxGapSx = maxGap(array, start, (end + start)/2);
		int maxGapDx = maxGap(array, (end + start)/2, end);
		if(maxGapSx >= maxGapDx){
			return maxGapSx;
		}
		else{
			return maxGapDx;
		}
	}
}