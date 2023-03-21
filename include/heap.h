#pragma once
#include "utils.h"

typedef struct {
	int *array;
	int size;
	int bottom; // Hari
} Heap;

Heap *createHeap(int size);
void free(Heap *heap);

Heap *heapify(int *array, int size);
Heap *heapify(int *array, int size, int heapSize);
int parent(int index);
int child(int index);
int child(int index, int n); // Nth child 1 or 2
Result insert(Heap *heap, int key);
Result remove(Heap *heap, int *key);
bool includes(Heap *heap, int key);
void print(Heap *heap);