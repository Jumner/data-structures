#include "avltrees.h"
#include "trees.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

avlNode *createAvlNode(int val) {
  avlNode *node = (avlNode*)malloc(sizeof(avlNode));
  node->val = val;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

avlTree *createAvlTree() {
  avlTree *tree = (avlTree*)malloc(sizeof(avlTree));
  tree->root = NULL;
  return tree;
}

avlTree *createAvlTree(avlNode *node) {
  avlTree *tree = createAvlTree();
  tree->root = node;
  return tree;
}
void free(avlNode *node) {
  free((bTreeNode*)node);
}
void free(avlTree *tree) {
  free((bTree*)tree);
}


Result find(avlTree *tree, int val, avlNode **pNode) {
  return find((bTree*)tree, val, (bTreeNode**)pNode);
}
Result find(avlNode *root, int val, avlNode **pNode) {
  return find((bTreeNode*)root, val, (bTreeNode**)pNode);
}

Result rotate(avlNode *root, Rotation rotation) {
  switch (rotation) {
    case R:
    return rotateR(root);
    break;
    case L:
    return rotateL(root);
    break;
    case LLR:
    return rotateLLR(root);
    break;
    case RRL:
    return rotateRRL(root);
    break;
    default:
    panic("Wrong rotation");
  }
  return ERR;
}

Result rotateR(avlNode *root) {
  if(root == NULL) return ERR;
  avlNode *newRoot = root->left;
  if(newRoot == NULL) return ERR;

  // int lh,rh;
  // lh = root->left != NULL ? root->left->height : 0;
  // rh = root->right != NULL ? root->right->height : 0;
  root->left = newRoot->right;
  newRoot->right = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;

  // Update heights
  root->height = max(root->height, root->left!=NULL?root->left->height+1:1);
  newRoot->height = max(newRoot->left!=NULL?newRoot->left->height+1:1,newRoot->right!=NULL?newRoot->right->height+1:1);
  return OK;
}

Result rotateL(avlNode *root) {
  if(root == NULL) return ERR;
  avlNode *newRoot = root->right;
  if(newRoot == NULL) return ERR;

  root->right = newRoot->left;
  newRoot->left = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;

  // Update heights
  root->height = max(root->height, root->right!=NULL?root->right->height+1:1);
  newRoot->height = max(newRoot->left!=NULL?newRoot->left->height+1:1,newRoot->right!=NULL?newRoot->right->height+1:1);
  return OK;
}

Result rotateLLR(avlNode *root) {
  if(root == NULL) return ERR;
  avlNode *leftChild = root->left;
  if(leftChild == NULL) return ERR;
  rotateL(leftChild); // Left rotate left child
  rotateR(root); // Right rotate
  return OK;
}

Result rotateRRL(avlNode *root) {
  if(root == NULL) return ERR;
  avlNode *rightChild = root->right;
  if(rightChild == NULL) return ERR;
  rotateR(rightChild); // Right rotate right child
  rotateL(root); // Left rotate
  return OK;
}

Result addNode(avlTree *tree, int val) {
  avlNode *node = createAvlNode(val);
  return insertNode(tree, node);
}

Result insertNode(avlTree *tree, avlNode *node) {
  return insertNode(&(tree->root), node);
}
Result insertNode(avlNode **pRoot, avlNode *node) {
  if(node == NULL || pRoot == NULL) return ERR;
  avlNode *root = *pRoot;
  if(root == NULL) { // First insert
    *pRoot = node;
    return OK;
  }

  avlNode *ancestor = NULL;
  while(root != NULL) {
    if(node->val > root->val) {
      if(root->right == NULL) { // Insert here
        root->right = node;
        break;
      }
      root = root->right;
    } else {
      if(root->left == NULL) { // Insert here
        root->left = node;
        break;
      }
      root = root->left;
    }
    if(balance(root) != Neutral) {
      ancestor = root;
    }
  }
  root->height = max(root->height, node->height+1);
  while(root->parent != NULL) { // Re traverse back up updating heights
    root->parent->height = max(root->parent->height, root->height+1);
    root = root->parent;
  }
  if(ancestor == NULL) return  OK; // Tree was complete, no balancing required
  Balance bf = balance(ancestor);
  if((bf == RHeavy && node->val < ancestor->val) || (bf == LHeavy && node->val > ancestor->val)) return OK; // Insert potentially bfs tree
  if(bf == TooRHeavy) { // Too right heavy
    if(balance(ancestor->right) == LHeavy) {
      rotateRRL(ancestor);
    } else {
      rotateL(ancestor);
    }
  }  else if (bf == TooLHeavy) {// Too left heavy
    if(balance(ancestor->left) == RHeavy) {
      rotateLLR(ancestor);
    } else {
      rotateR(ancestor);
    }
  }
  return OK;
}
Result deleteNode(avlTree *tree, int search) {
  avlNode *dNode;
  if (withdrawNode(tree, search, &dNode) == ERR) return ERR;;
  free(dNode);
  return OK;
}
Result withdrawNode(avlTree *tree, int search, avlNode **pNode) {
  if (tree->root == NULL) return ERR;
  return withdrawNode(&(tree->root), search, pNode);
}
Result withdrawNode(avlNode **pRoot, int search, avlNode **pNode) {
  if(pRoot == NULL || *pRoot == NULL || pNode == NULL) return ERR;
  // First, remove the element, we can fix it later
  avlNode *dNode;
  withdrawNode((bTreeNode*)pRoot, search, (bTreeNode**)pNode);
  avlNode *root = *pRoot;
  while(root != NULL) {
    Balance bf = balance(root);
    if(bf == TooRHeavy) {
      if (balance(root->right) == LHeavy) {
        rotateRRL(root);
      } else {
        rotateL(root);
      }
      break;
    } else if (bf == TooLHeavy) {
      if (balance(root->left) == RHeavy) {
        rotateLLR(root);
      } else {
        rotateR(root);
      }
      break;
    }
    if((*pNode)->val > root->val) {
      root = root->right;
    } else {
      root = root->left;
    }
  }
  return OK;
}
int height(avlNode *node) {
  if(node == NULL) return 0;
  node->height = max(height(node->left), height(node->right)) + 1;
  return node->height;
}
Balance balance(avlNode *node) {
  return (Balance)(height(node->left) - height(node->right));
}
void printTree(avlTree *tree) {
  printTree(tree, IN_ORDER);
}
void printTree(avlTree *tree, bTreeOrder order) {
  printTreePath(traverseTree(tree, order));
}
bTreePath traverseTree(avlTree *tree) {
  return traverseTree(tree, IN_ORDER);
}
bTreePath traverseTree(avlTree *tree, bTreeOrder order) {
  return traverseTree((bTree*)tree, order);
}
