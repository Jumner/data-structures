#pragma once
#include "linked_list.h"
#include "utils.h"
typedef struct {
  int front;
  int back;
  int count;
  int list[MAXSTACKSIZE];
} SequentialQueue;

SequentialQueue *createSequentialQueue();
Result push_back(SequentialQueue *queue, int val);
Result pop_front(SequentialQueue *queue, int *val);
int *peek_front(SequentialQueue *queue);
bool is_empty(SequentialQueue *queue);
void free(SequentialQueue *queue);

typedef struct {
  LinkedList *list;
} LinkedQueue;

LinkedQueue *createLinkedQueue();
Result push_back(LinkedQueue *queue, int val);
Result pop_front(LinkedQueue *queue, int *val);
int *peek_front(LinkedQueue *queue);
bool is_empty(LinkedQueue *queue);
void free(LinkedQueue *queue);
