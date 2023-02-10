#pragma once

#include "utils.h"
#include "linked_list.h"
#include "trees.h"
// Searching

// Linear search
Node *linearSearch(LinkedList *list, int val); // Blazingly fast without fearless concurency
int *linearSearch(int *list, int size, int val);

// Binary search
extern int arrayCompares; // Magic fr pls teach us extern
extern int linkedCompares;
Node *binarySearch(LinkedList *list, int val); // Cursed
Node *binarySearch(LinkedList *list, int val, Node *start, Node *end); // Cursed
int *binarySearch(int *list, int size, int val); // Not cursed

int treeSum(bTree *tree);
