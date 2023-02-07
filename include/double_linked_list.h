#pragma once

#include "linked_list.h"
#include "utils.h"

typedef struct dNode {
  int val;
  struct dNode *next;
  struct dNode *prev;
} DNode;

typedef struct {
  DNode *head;
  DNode *tail;
} DoubleLinkedList;

DNode *createDNode(int val);
DoubleLinkedList *createDoubleLinkedList();
DoubleLinkedList *createDoubleLinkedList(LinkedList *l);
void fix_prev(DoubleLinkedList *l);

int insert_head(DoubleLinkedList *l, int val);
int insert_tail(DoubleLinkedList *l, int val);
int insert_at(DoubleLinkedList *l, int search, int val);
int remove_head(DoubleLinkedList *l, int *val);
int remove_tail(DoubleLinkedList *l, int *val);
int remove_at(DoubleLinkedList *l, int search, int *val);
void free(DoubleLinkedList *l);
