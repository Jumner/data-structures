#pragma once
#include "utils.h"
#include "trees.h"

typedef struct avlNode { // AVL tree node
  int val;
  struct avlNode *parent;
  struct avlNode *left, *right;
  int height;
} avlNode;

typedef struct { // AVL tree
  avlNode *root;
} avlTree;

typedef enum {
  L, RRL, R, LLR
} Rotation;
typedef enum {
  TooRHeavy=-2, RHeavy=-1, LHeavy=1, TooLHeavy=2, Neutral=0
} Balance;

avlNode *createAvlNode(int val);
avlTree *createAvlTree();
avlTree *createAvlTree(avlNode *node);
void free(avlNode *node);
void free(avlTree *tree);

Result find(avlTree *tree, int val, avlNode **pNode); // Return node by ref
Result find(avlNode *root, int val, avlNode **pNode);
Result rotate(avlNode *root, Rotation rotation);
Result rotateR(avlNode *root);
Result rotateL(avlNode *root);
Result rotateLLR(avlNode *root);
Result rotateRRL(avlNode *root);
Result addNode(avlTree *tree, int val); // Insert into tree
Result insertNode(avlNode **pRoot, avlNode *node);
Result insertNode(avlTree *tree, avlNode *node);
Result deleteNode(avlTree *tree, int search);  // Delete a node
Result withdrawNode(avlNode **root, int search, avlNode **pNode);
Result withdrawNode(avlTree *tree, int search, avlNode **pNode); // Pass pointer by reference
int height(avlNode *node);
Balance balance(avlNode *node);
void printTree(avlTree *tree); // Print tree using in order
void printTree(avlTree *tree, bTreeOrder order); // Print tree using specified order
bTreePath traverseTree(avlTree *tree); // Return array in order of traveral using in order
bTreePath traverseTree(avlTree *tree, bTreeOrder order); // Return array in order of traveral
