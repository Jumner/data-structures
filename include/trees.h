#pragma once
#include "utils.h"

typedef struct bTreeNode { // Binary tree node
	int val;
	struct bTreeNode *parent;
	struct bTreeNode *left;
	struct bTreeNode *right;
} bTreeNode;

typedef struct { // Binary Tree
	bTreeNode *root;
} bTree;

typedef struct { // Tree Path
	int size;
	bTreeNode **list;
} bTreePath;

typedef enum {
	IN_ORDER, PRE_ORDER, POST_ORDER
} bTreeOrder;

bTreeNode *createBTreeNode(int val);
bTree *createBTree();
bTree createBTree(bTreeNode *node);
bTreePath createBTreePath();
bTreePath createBTreePath(bTreeNode *node);
void free(bTreeNode *node);
void free(bTree *tree);
void free(bTreePath path);

bool isEmpty(bTree *tree); // Tree is empty
bool isEmpty(bTreeNode *node);
bool isFull(bTree *tree, int val); // Node with val is full
bool isFull(bTreeNode *node);
Result find(bTree *tree, int val, bTreeNode **pNode); // Return node by ref
Result find(bTreeNode *root, int val, bTreeNode **pNode);
Result findParent(bTree *tree, int val, bTreeNode **pNode); // Return parent node
Result addNode(bTree *tree, int val); // Insert into tree
Result addNode(bTreeNode *root, int val); // Insert into tree
Result insertNode(bTreeNode *root, bTreeNode *node);
Result deleteNode(bTree *tree, int search);  // Delete a node
Result withdrawNode(bTreeNode *root, int search, bTreeNode **pNode);
Result withdrawNode(bTree *tree, int search, bTreeNode **pNode); // Pass pointer by reference
int depth(bTree *tree, bTreeNode *node);
int depth(bTreeNode *root, bTreeNode *node);
int treeHeight(bTree *tree); // Return tree's height
int treeHeight(bTreeNode *root);
void printTree(bTree *tree); // Print tree using in order
void printTree(bTree *tree, bTreeOrder order); // Print tree using specified order
bTreePath traverseTree(bTree *tree); // Return array in order of traveral using in order
bTreePath traverseTree(bTree *tree, bTreeOrder order); // Return array in order of traveral
bTreePath merge(bTreePath p1, bTreePath p2);
bTreePath merge(bTreePath p1, bTreePath p2, bTreePath p3);