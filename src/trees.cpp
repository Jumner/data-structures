#include "trees.h"
#include "avltrees.h"
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

Result find(bTreeNode *root, int val, bTreeNode **pNode) {
  if (root == NULL) return ERR;
  if(val == root->val) {
    *pNode = root;
    return OK;
  } else if (val > root->val) {
    return find(root->right, val, pNode);
  } else {
    return find(root->left, val, pNode);
  }
}

Result findParent(bTree *tree, int val, bTreeNode **pNode) {
  bTreeNode *node;
  if(find(tree, val, &node) == ERR) return ERR;
  if(node->parent == NULL) return ERR;
  *pNode = node->parent;
  return OK;
}

Result addNode(bTree *tree, int val) {
  if (tree->root == NULL) {
    tree->root = createBTreeNode(val);
    return OK;
  }
  return addNode(tree->root, val);
}

Result addNode(bTreeNode *root, int val) {
  if(root == NULL) return ERR;
  if(val > root->val) {
    if(root->right == NULL) {
      root->right = createBTreeNode(val);
      root->right->parent = root;
      return OK;
    }
    return addNode(root->right, val);
  } else if(val < root->val) {
    if(root->left == NULL) {
      root->left = createBTreeNode(val);
      root->left->parent = root;
      return OK;
    }
    return addNode(root->left, val);
  }
  return ERR; // Already in tree
}

Result insertNode(bTreeNode *root, bTreeNode *node) {
  if(root == NULL || node == NULL) return ERR;
  if(node->val > root->val) {
    if(root->right == NULL) {
      root->right = node;
      root->right->parent = root;
      return OK;
    }
    return insertNode(root->right, node);
  }
  else if (node->val < root->val) {
    if(root->left == NULL) {
      root->left = node;
      root->left->parent = root;
      return OK;
    }
    return insertNode(root->left, node);
  }
  return ERR;
}

Result deleteNode(bTree *tree, int search) {
  bTreeNode *del;
  if(withdrawNode(tree, search, &del) == ERR) return ERR; 
  free(del);
  return OK;
}

Result withdrawNode(bTree *tree, int search, bTreeNode **pNode) {
  if(tree->root == NULL) return ERR;
  return withdrawNode(tree->root, search, pNode);
}

Result withdrawNode(bTreeNode *root, int search, bTreeNode **pNode) { // Cant remove the root
  if(find(root, search, pNode) == ERR) return ERR; // Find node to remove and "return" it
  bTreeNode *dNode = *pNode;
  bTreeNode *nNode = NULL;
  // Go to the far right from the left side node to delete
  // This finds the node to replace the one to delete
  // Only needed if the delete node has children
  if(dNode->left != NULL) {
    for(nNode = dNode->left; nNode->right != NULL; nNode = nNode->right);
  } else if(dNode->right != NULL) { // Or the far left from the right
    for(nNode = dNode->right; nNode->left != NULL; nNode = nNode->left);
  }
  // Insert each of the deleted nodes children on their spots in the new node
  if(nNode != NULL) {
    nNode->parent->left == nNode ? nNode->parent->left = NULL : nNode->parent->right = NULL; // Remove nNode from its current place
    insertNode(nNode,dNode->left); // Put delete nodes children onto the new root
    insertNode(nNode,dNode->right);
    dNode->left = NULL; // Avoid circular shit if dNode is free'd
    dNode->right = NULL;
  }
  // Make the deleted nodes parent point to the new one and return
  if(dNode->parent != NULL) {
    if(nNode != NULL) {
      nNode->parent = dNode->parent; // New nodes parent pointer points to delete nodes parent
      dNode->parent->left == dNode ? dNode->parent->left = nNode : dNode->parent->right = nNode; // Delete nodes parent now points to new node
    } else {
      dNode->parent->left == dNode ? dNode->parent->left = NULL : dNode->parent->right = NULL; // Remove delete node from its parent
    }
    dNode->parent = NULL; // Fully remove delete node from the tree
  }
  return OK;
}

int depth(bTreeNode *root, bTreeNode *node) {
  bTreeNode *temp = root;
  int i;
  for(i = 0; temp != node; i ++) {
    if (temp == NULL) return -1;
    if(node->val > temp->val) {
      temp = temp->right;
    } else {
      temp = temp->left;
    }
  }
  return i;
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
  printTreePath(traverseTree(tree, order));
}
void printTreePath(bTreePath path) {
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
  bTreePath p1 = traverseTreeInOrder((bTreeNode*)(root->left));
  bTreePath p2 = createBTreePath((bTreeNode*)(root));
  bTreePath p3 = traverseTreeInOrder((bTreeNode*)(root->right));
  return merge(p1,p2,p3);
}

bTreePath traverseTreePreOrder(bTreeNode *root) {
  if (root == NULL) {return createBTreePath();}
  bTreePath p1 = createBTreePath((bTreeNode*)(root));
  bTreePath p2 = traverseTreePreOrder((bTreeNode*)(root->left));
  bTreePath p3 = traverseTreePreOrder((bTreeNode*)(root->right));
  return merge(p1,p2,p3);
}

bTreePath traverseTreePostOrder(bTreeNode *root) {
  if (root == NULL) {return createBTreePath();}
  bTreePath p1 = traverseTreePostOrder((bTreeNode*)(root->left));
  bTreePath p2 = traverseTreePostOrder((bTreeNode*)(root->right));
  bTreePath p3 = createBTreePath((bTreeNode*)(root));
  return merge(p1, p2, p3);
}

bTreePath traverseTree(bTree *tree, bTreeOrder order) {
  bTreePath path;
  switch (order) {
    case IN_ORDER:
      path = traverseTreeInOrder((bTreeNode*)(tree->root));
      break;
    case PRE_ORDER:
      path = traverseTreePreOrder((bTreeNode*)(tree->root));
      break;
    case POST_ORDER:
      path = traverseTreePostOrder((bTreeNode*)(tree->root));
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