#include "linked_list.h"
#include "utils.h"
#include <cstdio>
#include <stdlib.h>

Node *createNode(int val) {
  Node *p_new = (Node *)malloc(sizeof(Node));
  if (p_new == NULL) {
    panic("Could not allocate node");
  }
  p_new->val = val;
  p_new->next = NULL;
  return p_new;
}

LinkedList *createLinkedList() {
  LinkedList *l_new = (LinkedList *)malloc(sizeof(LinkedList));
  if (l_new == NULL) {
    panic("Could not allocate linkedlist");
  }
  l_new->head = NULL;
  return l_new;
}

LinkedList *createLinkedList(int *array, int size) {
  LinkedList *l = createLinkedList();
  for(int i = size-1; i >= 0; i --) {
    insert_head(l, array[i]);
  }
  return l;
}

Result insert_head(LinkedList *l, int val) {
  Node *p_new = createNode(val);
  p_new->next = l->head;
  l->head = p_new;
  return OK;
}

Result insert_tail(LinkedList *l, int val) {
  Node *p_new = createNode(val);
  Node *p_temp = l->head;
  if(l->head == NULL) {
    l->head = p_new;
    return OK;
  }
  while (p_temp->next != NULL) {
    p_temp = p_temp->next;
  }
  p_temp->next = p_new;
  return OK;
}

Result insert_at(LinkedList *l, int search, int val) {
  Node *p_temp = l->head;
  if(p_temp == NULL) return ERR;
  while (p_temp->next != NULL && p_temp->val != search) {
    p_temp = p_temp->next;
  }
  if (p_temp->val != search) {
    return ERR;
  }
  Node *p_new = createNode(val);
  p_new->next = p_temp->next;
  p_temp->next = p_new;
  return OK;
}

Result remove_head(LinkedList *l, int *val) {
  if (l->head == NULL) {
    return ERR;
  }
  Node *d_node = l->head;
  l->head = d_node->next;

  *val = d_node->val;
  free(d_node);
  return OK;
}

Result remove_tail(LinkedList *l, int *val) {
  if(l->head == NULL) return ERR;
  Node **pp_temp = &(l->head);

  while((*pp_temp)->next != NULL) {
    pp_temp = &((*pp_temp)->next);
  }
  *val = (*pp_temp)->val;
  free(*pp_temp);
  *pp_temp = NULL;
  return OK;
}

Result remove_at(LinkedList *l, int search, int *val) {
  Node **pp_temp = &(l->head);
  while (*pp_temp != NULL && (*pp_temp)->val != search) {
    pp_temp = &((*pp_temp)->next);
  }
  if (*pp_temp == NULL)
    return ERR;

  Node *p_temp = *pp_temp;
  *val = p_temp->val;
  *pp_temp = p_temp->next;
  free(p_temp);
  return OK;
}

void free(LinkedList *l) {
  int val;
  while(remove_head(l, &val) == OK) continue;
  free((void*)l);
}
