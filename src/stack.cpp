#include "stack.h"
#include "linked_list.h"
#include <stdlib.h>

SequentialStack *createSequentialStack() {
  SequentialStack *stack = (SequentialStack *)malloc(sizeof(SequentialStack));
  if (stack == NULL) {
    // ERR
  }
  stack->top = -1;
  return stack;
}

int push(SequentialStack *stack, int val) { 
  if (stack->top >= MAXSTACKSIZE - 1) return ERR;
  stack->items[++stack->top] = val;
  return OK;
}
int pop(SequentialStack *stack) {
  return pop(stack, NULL);
}
int pop(SequentialStack *stack, int *val) { 
  if (stack->top < 0) return ERR;
  if(val != NULL) {
    *val = stack->items[stack->top];
  }
  stack->top--;
  return OK;
}
int *peek(SequentialStack *stack) { return &(stack->items[stack->top]); }
void free(SequentialStack *stack) {
  free((void*)stack);
}

LinkedStack *createLinkedStack() {
  LinkedStack *stack = (LinkedStack *)malloc(sizeof(LinkedStack));
  if (stack == NULL) {
    // ERR
  }
  stack->list = (createLinkedList());
  return stack;
}

void push(LinkedStack *stack, int val) {
  insert_head(stack->list, val);
}

int pop(LinkedStack *stack, int *val) {
  return remove_head(stack->list, val);
}

int *peek(LinkedStack *stack) { return &(stack->list->head->val); }
void free(LinkedStack *stack) {
  free(stack->list);
  free((void*)stack);
}
