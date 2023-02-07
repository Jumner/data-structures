#include "queue.h"
#include "utils.h"
#include "linked_list.h"
#include <stdlib.h>

SequentialQueue *createSequentialQueue() {
  SequentialQueue *queue = (SequentialQueue *)malloc(sizeof(SequentialQueue));
  if (queue == NULL) {
    // ERR
  }
  queue->back = -1;
  queue->front = -1;
  queue->count = 0;
  return queue;
}

int push_back(SequentialQueue *queue, int val) {
  if (queue->count == MAXSTACKSIZE) return ERR;
  queue->back = ++queue->back % MAXSTACKSIZE;
  queue->list[queue->back] = val;
  if (queue->front == -1) {
    queue->front = queue->back;
  }
  queue->count++;
  return OK;
}

int pop_front(SequentialQueue *queue, int *val) {
  if(queue->count <= 0) return ERR;
  *val = queue->list[queue->front];
  queue->front = ++queue->front % MAXSTACKSIZE;
  queue->count--;
  if (is_empty(queue)) {
    queue->front = queue->back = -1;
  }
  return OK;
}
int *peek_front(SequentialQueue *queue) { return &(queue->list[queue->front]); }
bool is_empty(SequentialQueue *queue) { return queue->count == 0; }
void free(SequentialQueue *queue) {
  free((void*)queue);
}

LinkedQueue *createLinkedQueue() {
  LinkedQueue *queue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
  if (queue == NULL) {
    // ERR
  }
  queue->list = (createLinkedList());
  return queue;
}
int push_back(LinkedQueue *queue, int val) {
  return insert_tail(queue->list, val);
}
int pop_front(LinkedQueue *queue, int *val) {
  return remove_head(queue->list, val);
}
int *peek_front(LinkedQueue *queue) {
  return &(queue->list->head->val);
}
bool is_empty(LinkedQueue *queue) {
  return (queue->list->head == NULL);
}
void free(LinkedQueue *queue) {
  free(queue->list);
  free((void*)queue);
}
