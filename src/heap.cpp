#include "utils.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap *createHeap(int size) {
	Heap *heap = (Heap*)malloc(sizeof(Heap));
	heap->size = size;
	heap->bottom = 0;
	heap->array = (int*)malloc(heap->size * sizeof(int));
	return heap;
}

void free(Heap *heap) {
	free(heap->array);
	free((void*)heap);
}

void fixParent(Heap *heap, int par) {
		while(child(par) <= heap->bottom) {
		int great = child(par,2) > heap->bottom ? 
			0 : (heap->array[child(par,1)] > heap->array[child(par,2)] ? 0 : 1);
		great += child(par);
		if(heap->array[great] > heap->array[par]) {
			int temp = heap->array[par];
			heap->array[par] = heap->array[great];
			heap->array[great] = temp;
		}
		par = great;
	}
}

Heap *heapify(int *array, int size) {
	return heapify(array, size, size);
}

Heap *heapify(int *array, int size, int heapSize) {
	int last = size-1;
	Heap *heap = createHeap(heapSize);
	memcpy(heap->array, array, size*sizeof(int));
	heap->bottom = last;
	for(int index = last - 1 + last%2;index > 0; index -= 2) {
		// Fix parent
		fixParent(heap, parent(index));
	}
	return heap;
}

int parent(int index) {
	if(index == 0) return -1;
	return (index-1)/2;
}

int child(int index) {
	return 2*index+1;
}

int child(int index, int n) {
	if (n > 2 || n < 1) return -1;
	return 2*index+n;
}

Result insert(Heap *heap, int key) {
	if(heap->bottom >= heap->size-1) return ERR;
	int index = ++heap->bottom;
	heap->array[index] = key;
	while(parent(index) != -1 && heap->array[index] > heap->array[parent(index)]) {
		int temp = heap->array[parent(index)];
		heap->array[parent(index)] = heap->array[index];
		heap->array[index] = temp;
		index = parent(index);
	}
	return OK;
}

Result remove(Heap *heap, int *key) {
	if(heap->bottom < 0) return ERR; // Empty
	*key = heap->array[0];
	heap->array[0] = heap->array[heap->bottom--]; // "Swap" last item with root
	int index = 0;
	while(index < heap->bottom) {
		int temp = heap->array[index];
		int nth = heap->array[child(index,1)] > heap->array[child(index, 2)] ? 1 : 2;
		heap->array[index] = heap->array[child(index,nth)];
		heap->array[child(index,nth)] = temp;
		index = child(index, nth);
	}
	return OK;
}

bool includes(Heap *heap, int key) {
	for(int i = 0; i <= heap->bottom; i++) {
		if(heap->array[i] == key) {
			return true;
		}
	}
	return false;
}

void print(Heap *heap) {
	printf("Heap:\n");
	for(int i = 0; i <= heap->bottom; i ++) {
		printf("%i, ", heap->array[i]);
	}
	printf("\n");
}