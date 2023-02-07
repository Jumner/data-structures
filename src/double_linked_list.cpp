#include "double_linked_list.h"
#include <stdlib.h>

DNode *createDNode(int val) {
  DNode *p_new = (DNode *)malloc(sizeof(DNode));
  if (p_new == NULL) {
    // ERR
  }
  p_new->val = val;
  p_new->next = NULL;
  p_new->prev = NULL;
  return p_new;
}

DoubleLinkedList *createDoubleLinkedList() {
  DoubleLinkedList *l_new =
      (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
  if (l_new == NULL) {
    // ERR
  }
  l_new->head = NULL;
  l_new->tail = NULL;
  return l_new;
}

DoubleLinkedList *createDoubleLinkedList(LinkedList *l) {
  DoubleLinkedList *dl = createDoubleLinkedList();
  Node *p_node = l->head;
  DNode **pp_dNode = &(dl->head);
  DNode *p_dTemp;
  while (p_node != NULL) {
    p_dTemp = createDNode(p_node->val);
    *pp_dNode = p_dTemp;
    pp_dNode = &(*pp_dNode)->next;

    p_node = p_node->next;
  }
  dl->tail = p_dTemp;

  fix_prev(dl);

  return dl;
}

void fix_prev(DoubleLinkedList *l) {
  DNode *p_temp = l->head;
  DNode *p_last = NULL;
  while (p_temp != NULL) {
    if (p_last != NULL) {
      p_temp->prev = p_last;
    }
    p_last = p_temp;
    p_temp = p_temp->next;
  }
}

int insert_head(DoubleLinkedList *l, int val) {
  DNode *p_temp = createDNode(val);
  p_temp->next = l->head;
  if (p_temp->next != NULL) {
    p_temp->next->prev = p_temp;
  } else {
    l->tail = p_temp;
  }
  l->head = p_temp;
  return OK;
}

int insert_tail(DoubleLinkedList *l, int val) {
  DNode *p_temp = createDNode(val);
  p_temp->prev = l->tail;
  if (p_temp->prev != NULL) {
    p_temp->prev->next = p_temp;
  } else {
    l->head = p_temp;
  }
  l->tail = p_temp;
  return OK;
}

int insert_at(DoubleLinkedList *l, int search, int val) {
  DNode *p_temp = l->head;
  while (p_temp != NULL && p_temp->val != search) {
    p_temp = p_temp->next;
  }
  if (p_temp->val != search) {
    return ERR;
  }
  DNode *p_new = createDNode(val);
  p_temp->next->prev = p_new;
  p_new->next = p_temp->next;
  p_new->prev = p_temp;
  p_temp->next = p_new;

  if (p_new->next == NULL) {
    l->tail = p_new;
  }
  return OK;
}

int remove_head(DoubleLinkedList *l, int *val) {
  DNode *r_node = l->head;
  if (r_node == NULL)
    return ERR;

  *val = r_node->val;
  l->head = r_node->next;
  if (l->head == NULL) {
    l->tail = NULL;
  } else {
    l->head->prev = NULL;
  }
  free(r_node);
  return OK;
}

int remove_tail(DoubleLinkedList *l, int *val) {
  DNode *r_node = l->tail;
  if (r_node == NULL)
    return ERR;

  *val = r_node->val;
  l->tail = r_node->prev;
  if (l->tail == NULL) {
    l->head = NULL;
  } else {
    l->tail->next = NULL;
  }
  free(r_node);
  return OK;
}

int remove_at(DoubleLinkedList *l, int search, int *val) {
  DNode *p_temp = l->head;

  while (p_temp != NULL && p_temp->val != search) {
    p_temp = p_temp->next;
  }
  if (p_temp->val != search)
    return ERR;

  DNode *r_node = p_temp;
  *val = r_node->val;
  if (r_node->prev == NULL) {
    l->head = r_node->next;
  } else {
    r_node->prev->next = r_node->next;
  }
  if (r_node->next == NULL) {
    l->tail = r_node->prev;
  } else {
    r_node->next->prev = r_node->prev;
  }

  free(r_node);
  return OK;
}

void free(DoubleLinkedList *l) {
  int val;
  while(remove_head(l, &val) == OK) continue;
  free((void*)l);
}
