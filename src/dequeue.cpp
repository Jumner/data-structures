#include "dequeue.h"
#include "utils.h"
#include "double_linked_list.h"
#include <stdlib.h>

Dequeue *createDequeue() {
  Dequeue *queue = (Dequeue*)malloc(sizeof(Dequeue));
  if(queue == NULL) {
    // ERR
  }
  queue->list = createDoubleLinkedList();
  return queue;
}
void push_front(Dequeue *queue, int val) {
  insert_head(queue->list, val);
}
void push_back(Dequeue *queue, int val) {
  insert_tail(queue->list, val);
}
int pop_front(Dequeue *queue, int *val) {
  return remove_head(queue->list, val);
}
int pop_back(Dequeue *queue, int *val) {
  return remove_tail(queue->list, val);
}
int *peek_front(Dequeue *queue) {
  return &(queue->list->head->val);
}
int *peek_back(Dequeue *queue) {
  return &(queue->list->tail->val);
}
bool is_empty(Dequeue *queue) {
  return queue->list->head == NULL;
}
void free(Dequeue *queue) {
  free(queue->list);
  free((void*)queue);
}