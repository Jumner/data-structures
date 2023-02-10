#include "trees.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

bTreeNode *createBTreeNode(int val) {
  bTreeNode *node = (bTreeNode*)malloc(sizeof(bTreeNode));
  if(node == NULL) panic("Could not allocate bTreeNode");
  node->val = val;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

bTree *createBTree() {
  bTree *tree = (bTree*)malloc(sizeof(bTree));
  if(tree == NULL) panic("Could not allocate bTree");
  tree->root = NULL;
  return tree;
}

bTree createBTree(bTreeNode *node) {
  bTree tree;
  tree.root = node;
  return tree;
}

bTreePath createBTreePath() {
  bTreePath path;
  path.size = 0;
  path.list = NULL;
  return path;
}

bTreePath createBTreePath(bTreeNode *node) {
  bTreePath path;
  path.size = 1;
  path.list = (bTreeNode**)malloc(sizeof(bTreeNode*));
  path.list[0] = node;
  return path;
}

void free(bTreeNode *node) {
  if(node == NULL) return;
  free(node->left);
  free(node->right);

  free((void*)node);
}

void free(bTree *tree) {
  free(tree->root);

  free((void*)tree);
}

void free(bTreePath path) {
  free((void*)(path.list));
}

bool isEmpty(bTree *tree) {
  return tree->root == NULL;
}

bool isEmpty(bTreeNode *node) {
  return (node->left == NULL && node->right == NULL);
}

bool isFull(bTree *tree, int val) {
  bTreeNode *node;
  if(find(tree, val, &node) == ERR) return true; // ERR i miss rust ;(
  return isFull(node);
}

bool isFull(bTreeNode *node) {
  return (node->left != NULL && node->right != NULL);
}

Result find(bTree *tree, int val, bTreeNode **pNode) {
  return find(tree->root, val, pNode);
}

Result find(bTreeNode *root, int val, bTreeNode **pNode) { // Uses pre-order
  if(root == NULL) return ERR; // I will not be caught lacking
  if (root->val == val) { // Root is it
    *pNode = root;
    return OK;
  }
  // Check left then right
  if(find(root->left,  val, pNode) == OK) return OK;
  if(find(root->right, val, pNode) == OK) return OK;
  return ERR; // None found, err
}

Result findParent(bTree *tree, int val, bTreeNode **pNode) {
  bTreeNode *node;
  if(find(tree, val, &node) == ERR) return ERR;
  if(node->parent == NULL) return ERR;
  *pNode = node->parent;
  return OK;
}

Result addNode(bTree *tree, int search, int val) {
  bTreeNode *node;
  if(find(tree, search, &node) == ERR) return ERR;
  return addNode(node, val);
}

Result addNode(bTree *tree, int val) {
  if(tree->root != NULL) return ERR;
  bTreeNode *node = createBTreeNode(val);
  tree->root = node;
  return OK;
}

Result addNode(bTreeNode *root, int val) {
  if(root->left == NULL) {
    bTreeNode *newNode = createBTreeNode(val);
    root->left = newNode;
    newNode->parent = root;
    return OK;
  } else if (root->right == NULL) {
    bTreeNode *newNode = createBTreeNode(val);
    root->right = newNode;
    newNode->parent = root;
    return OK;
  }
  return ERR; // Full
}

Result insertNode(bTree *tree, int search, bTreeNode *newNode) {
  bTreeNode *root;
  if(find(tree, search, &root) == ERR) return ERR;
  if(root->left != NULL) (root->left = newNode, newNode->parent = root);
  else if(root->right != NULL) (root->right = newNode, newNode->parent = root);
  else {return ERR;}
  return OK;
}

Result deleteNode(bTree *tree, int search) {
  bTreeNode *del;
  if(withdrawNode(tree, search, &del) == ERR) return ERR; 
  free(del);
  return OK;
}

Result withdrawNode(bTree *tree, int search, bTreeNode **pNode) {
  bTreeNode *del;
  if(find(tree, search, &del) == ERR) return ERR;
  if(del->parent->left == del) {
    del->parent->left = NULL;
  } else if(del->parent->right == del) {
    del->parent->right = NULL;
  }
  *pNode = del;
  return OK;
}

int depth(bTreeNode *root, bTreeNode *node) {
  if(root->left != NULL) {
    if(root->left == node) return 1;
    int d = depth(root->left, node);
    if(d != -1) return 1+d;
  }
  if(root->right != NULL) {
    if(root->right == node) return 1;
    int d = depth(root->right, node);
    if(d != -1) return 1+d;
  } 
  return -1;
}

int depth(bTree *tree, bTreeNode *node) {
  if(tree->root == NULL) return -1;
  return depth(tree->root, node);
}

int treeHeight(bTree *tree) {
  return treeHeight(tree->root);
}

int treeHeight(bTreeNode *root) {
  if(root == NULL) return -1;
  int lh = 1+treeHeight(root->left);
  int rh = 1+treeHeight(root->right);
  return lh>rh ? lh : rh;
}

void printTree(bTree *tree) {
  printTree(tree, IN_ORDER);
}

void printTree(bTree *tree, bTreeOrder order) {
  bTreePath path = traverseTree(tree, order);
  for(int i = 0; i < path.size; i ++) {
    printf("%i", path.list[i]->val);
    if(i+1 < path.size) {
      printf(", ");
    }
  }
  printf("\n");
}

bTreePath traverseTree(bTree *tree) {
  return traverseTree(tree, IN_ORDER);
}

bTreePath traverseTreeInOrder(bTreeNode *root) {
  if (root == NULL) {return createBTreePath();}
  bTreePath p1 = traverseTreeInOrder(root->left);
  bTreePath p2 = createBTreePath(root);
  bTreePath p3 = traverseTreeInOrder(root->right);
  return merge(p1,p2,p3);
}

bTreePath traverseTreePreOrder(bTreeNode *root) {
  if (root == NULL) {return createBTreePath();}
  bTreePath p1 = createBTreePath(root);
  bTreePath p2 = traverseTreePreOrder(root->left);
  bTreePath p3 = traverseTreePreOrder(root->right);
  return merge(p1,p2,p3);
}

bTreePath traverseTreePostOrder(bTreeNode *root) {
  if (root == NULL) {return createBTreePath();}
  bTreePath p1 = traverseTreePostOrder(root->left);
  bTreePath p2 = traverseTreePostOrder(root->right);
  bTreePath p3 = createBTreePath(root);
  return merge(p1, p2, p3);
}

bTreePath traverseTree(bTree *tree, bTreeOrder order) {
  bTreePath path;
  switch (order) {
    case IN_ORDER:
      path = traverseTreeInOrder(tree->root);
      break;
    case PRE_ORDER:
      path = traverseTreePreOrder(tree->root);
      break;
    case POST_ORDER:
      path = traverseTreePostOrder(tree->root);
      break;
    default:
      panic("Wrong bTreeOrder");
  }
  return path;
}

bTreePath merge(bTreePath p1, bTreePath p2) {
  bTreePath path;
  path.size = p1.size + p2.size;
  path.list = (bTreeNode**)malloc(path.size*sizeof(bTreeNode*));
  for(int i = 0; i < p1.size; i ++) {
    path.list[i] = p1.list[i];
  }
  for(int i = 0; i < p2.size; i ++) {
    path.list[i+p1.size] = p2.list[i];
  }

  free(p1);
  free(p2);
  return path;
}

bTreePath merge(bTreePath p1, bTreePath p2, bTreePath p3) {return merge(merge(p1,p2),p3);}