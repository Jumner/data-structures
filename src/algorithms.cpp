#include <cstdio>
#include <stdlib.h>
#include "utils.h"
#include "linked_list.h"

#include "algorithms.h"

#define VERBOSE false

int arrayCompares=0; // How tf does this work I hate it here
int linkedCompares=0;

Node *linearSearch(LinkedList *list, int val) {
  Node *p_search = list->head;
  while(p_search != NULL && p_search->val != val) {
    p_search = p_search->next;
  }
  if(p_search->val != val) {
    return NULL; // Item could not be found
  }
  return p_search; // Item found return it
}
int *linearSearch(int *list, int size, int val) {
  for(int i = 0; i < size; i ++) {
    if(list[i] == val) return &list[i];
  }
  return NULL;
}

Node *binarySearch(LinkedList *list, int val) {
  return binarySearch(list, val, list->head, NULL);
}
Node *binarySearch(LinkedList *list, int val, Node *start, Node *end) {
  if (VERBOSE) printf("\nrange %i - %i\n", start==NULL ? -1 : start->val, end==NULL ? -1 : end->val);
  if (start == end) { // Oopsie doopsie! Item not found ;(
    // I stg I'm 100% gonna deref the result of a binary search and segfault when I forgor it can return NULL
    // And no! I refuse to pass in a double node pointer and make the function return OK/ERR
    return NULL; 
  }

  // Traverse trav from start to end, mid moves once and trav moves twice
  Node *mid = start; 
  for(Node *trav = start; trav->next != end;) {
    trav = trav->next;
    if (trav->next == end) break; // No segfaults (core dumped) please :p
    mid = mid->next;
    trav = trav->next;
  }

  // Mid is now in between start and end
  if (VERBOSE) printf("mid: %i\n", mid->val);

  if (++linkedCompares && mid->val == val) { // Do data comparisons
    if (VERBOSE) printf("Item found %i\n", mid->val);
    return mid; // Item found
  } else if (++linkedCompares && mid->val > val) {
    end = mid; // Went to far, go from start to mid
  } else {
    start = mid->next; // Didnt go far enough. Go from after mid to end
  }
  
  return binarySearch(list, val, start, end); // Recursion!!!!
}

int *binarySearch(int *list, int size, int val) {
  int start = 0;
  int end = size-1;

  while(end >= start) {
    if (VERBOSE) printf("Arr: %i - %i\n", list[start], list[end]);
    int mid = start + (end - start)/2; // Calculate midpoint
    if (VERBOSE) printf("Mid: %i\n", list[mid]);
    if(++arrayCompares && list[mid] == val) return &list[mid]; // Compare midpoint
    else if (++arrayCompares && list[mid] > val) end = mid-1; // Wasn't it check which way to go
    else start = mid + 1;
    // Note, the code here end = mid-1, in the other one it stops one early so they're equivilent
  }
  return NULL;
}
