#pragma once
#include "utils.h"
#include "double_linked_list.h"

typedef struct {
	DoubleLinkedList *list;
} Dequeue;

Dequeue *createDequeue();
void push_front(Dequeue *queue, int val);
void push_back(Dequeue *queue, int val);
Result pop_front(Dequeue *queue, int *val);
Result pop_back(Dequeue *queue, int *val);
int *peek_front(Dequeue *queue);
int *peek_back(Dequeue *queue);
bool is_empty(Dequeue *queue);
void free(Dequeue *queue);