#pragma once
#include "linked_list.h"
#include "utils.h"

typedef struct {
  int top;
  int items[MAXSTACKSIZE];
} SequentialStack;

SequentialStack *createSequentialStack();
Result push(SequentialStack *stack, int val);
Result pop(SequentialStack *stack);
Result pop(SequentialStack *stack, int *val);
int *peek(SequentialStack *stack); // Top of stack
void free(SequentialStack *stack);

typedef struct {
  LinkedList *list;
} LinkedStack;

LinkedStack *createLinkedStack();
void push(LinkedStack *stack, int val);
Result pop(LinkedStack *stack, int *val);
int *peek(LinkedStack *stack); // Top of stack
void free(LinkedStack *stack);
