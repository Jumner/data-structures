#pragma once

#include "utils.h"

typedef struct node {
  int val;
  struct node *next;
} Node;

typedef struct {
  Node *head;
} LinkedList;

Node *createNode(int val);
LinkedList *createLinkedList();
LinkedList *createLinkedList(int *array, int size);

Result insert_head(LinkedList *l, int val);
Result insert_tail(LinkedList *l, int val);
Result insert_at(LinkedList *l, int search, int val);
Result remove_head(LinkedList *l, int *val);
Result remove_tail(LinkedList *l, int *val);
Result remove_at(LinkedList *l, int search, int *val);
void free(LinkedList *l);
