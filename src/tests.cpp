#include "tests.h"
#include "utils.h"
#include <cstdio>
#include <stdlib.h>
#include "linked_list.h"
#include "double_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "dequeue.h"
#include "trees.h"
#include "avltrees.h"
#include "hash.h"
#include "heap.h"
#include "algorithms.h"
// Tests
Result linkedListBinarySearchTest() {
	int array[11] = {0,3,6,7,8,11,14,21,45,54,56};
	LinkedList *list = createLinkedList(array, 11);
	int val;
	printf("\n");
	for(int i = 0; remove_head(list, &val) == OK; i++) {
		(VERBOSE && printf("%i ", val)); // 0 3 6 7 ...
		if(val != array[i]) return ERR;
	}; 
	list = createLinkedList(array, 11);
	if(linearSearch(list, 45) != binarySearch(list, 45) || linearSearch(array, 11, 45) != binarySearch(array, 11, 45)) {
	 	if (VERBOSE) printf("Uh oh linear and binary search are fighting again\n");
		return ERR;
	}
	if(binarySearch(list, 0) == NULL || binarySearch(list, 56) == NULL || binarySearch(list, 9) != NULL) {
		if (VERBOSE) printf("Uh oh binary search is misbehaving\n");
		return ERR;
	}
	if(binarySearch(array, 11, 0) == NULL || binarySearch(array, 11, 56) == NULL || binarySearch(array, 11, 9) != NULL) {
		if (VERBOSE) printf("Smh my head\n");
		return ERR;
	}
	if(arrayCompares != linkedCompares) {
		if (VERBOSE) printf("I should drop out frfr no cap\n");
		return ERR;
	}
	if (VERBOSE) printf("\nArray compares:  %i\nLinked compares: %i\n", arrayCompares, linkedCompares);
	printf("Binary Search === PASS\n");
	return OK;
}

Result linkedListTest() {
	LinkedList *list = createLinkedList();
	insert_head(list, 2);
	insert_head(list, 1);
	insert_head(list, 0);
	insert_tail(list, 3);
	insert_at(list, 2, 69);
	insert_tail(list, 5);
	insert_tail(list, 6);
	insert_at(list, 3, 4);
	int val;
	remove_at(list, 69, &val);
	if (VERBOSE) printf("%i ", val); // 69
	if(val != 69) return ERR;
	int expected[7] = {0,1,2,6,5,4,3};
	for(int i = 0; i < 3; i ++) {
		remove_head(list, &val);
		if (VERBOSE) printf("%i ", val); // 0 1 2
		if(val != expected[i]) return ERR;
	}
	for(int i = 3; remove_tail(list, &val) == OK; i ++) {
		if (VERBOSE) printf("%i ", val); // 6 5 4 3
		if(val != expected[i]) return ERR;
	}
	free(list);
	printf("Linked list === PASS\n");
	return linkedListBinarySearchTest();
}


Result doubleLinkedListTest() {
	DoubleLinkedList *list = createDoubleLinkedList();
	insert_head(list, 2);
	insert_head(list, 1);
	insert_head(list, 0);
	insert_tail(list, 3);
	insert_at(list, 2, 69);
	insert_tail(list, 5);
	insert_tail(list, 6);
	insert_at(list, 3, 4);
	int val;
	remove_at(list, 69, &val);
	if (VERBOSE) printf("%i ", val); // 69
	if(val != 69) return ERR;
	int expected[12] = {0,1,2,6,5,4,3,5,4,3,2,1};
	for(int i = 0; i < 3; i ++) {
		remove_head(list, &val);
		if (VERBOSE) printf("%i ", val); // 0 1 2
		if (val != expected[i]) return ERR;
	}
	for(int i = 3; remove_tail(list, &val) == OK; i ++) {
		if (VERBOSE) printf("%i ", val); // 6 5 4 3
		if (val != expected[i]) return ERR;
	}
	if (VERBOSE) printf("\n");
	LinkedList *slist = createLinkedList();
	insert_tail(slist, 5);
	insert_tail(slist, 4);
	insert_tail(slist, 3);
	insert_tail(slist, 2);
	insert_tail(slist, 1);
	list = createDoubleLinkedList(slist);
	free(slist);
	for(int i = 7; remove_head(list, &val); i++) {
		if (VERBOSE) printf("%i ", val); // 5 4 3 2 1
		if (val != expected[i]) return ERR;
	}
	free(list);
	printf("Double linked list === PASS\n");
	return OK;
}

Result sequentialStackTest() {
	SequentialStack *stack = createSequentialStack();
	int expected[16];
	for(int i = 0; i < 16; i ++) {
		push(stack, 16-i);
		expected[i] = 1+i;
	}
	if (VERBOSE) printf("%i ", *peek(stack)); // 1
	if(*peek(stack) != 1) return ERR;
	int val;
	for(int i = 0;pop(stack, &val) == OK; i ++) {
		if (VERBOSE) printf("%i ", val); // 1 - 16
		if (val != expected[i]) return ERR;
	}
	// Fill Test
	for(int i = 0; push(stack, i) == OK; i ++) continue;
	if (VERBOSE) printf("\n%i ", *peek(stack)); // 99
	if (*peek(stack) != 99) return ERR;
	for(val = 0; pop(stack); val++);
	if (VERBOSE) printf("\n%i\n", val); // 100
	if (val != 100) return ERR;
	free(stack);
	printf("Sequential stack === PASS\n");
	return OK;
}

Result linkedStackTest() {
	LinkedStack *stack = createLinkedStack();
	int expected[16];
	for(int i = 0; i < 16; i ++) {
		push(stack, 16-i);
		expected[i] = 1+i;
	}
	if (VERBOSE) printf("%i ", *peek(stack)); // 1
	if (*peek(stack) != 1) return ERR;
	int val;
	for(int i = 0; pop(stack, &val) == OK; i ++) {
		if (VERBOSE) printf("%i ", val); // 1 - 16
		if (val != expected[i]) return ERR;
	}
	free(stack);
	printf("Linked stack === PASS\n");
	return OK;
}

Result stackTest() {
	if (sequentialStackTest() == ERR) return ERR;
	printf("\n");
	if (linkedStackTest() == ERR) return ERR;
	return OK;
}

Result sequentialQueueTest() {
	SequentialQueue *queue = createSequentialQueue();
	if(!is_empty(queue) && VERBOSE) printf("Queue is empty not full?");
	if(!is_empty(queue)) return ERR;
	int expected[16];
	for(int i = 0; i < 16; i ++) {
		push_back(queue, i+1);
		expected[i] = i+1;
	}
	if (VERBOSE) printf("%i ", *peek_front(queue)); // 1
	if(*peek_front(queue) != 1) return ERR;
	int val;
	for(int i = 0; pop_front(queue, &val) == OK; i++) {
		if (VERBOSE) printf("%i ", val); // 1 - 16
		if (val != expected[i]) return ERR;
	}
	// Fill test
	if (VERBOSE) printf("\n");
	for(int i = 0; push_back(queue, i+1) == OK; i ++) continue;
	if (is_empty(queue)) return ERR;
	for(val = 0; pop_front(queue, &val) == OK; (VERBOSE && printf("%i ", val))) continue;
	if (!is_empty(queue)) return ERR;
	free(queue);
	printf("Sequential queue === PASS\n");
	return OK;
}

Result linkedQueueTest() {
	LinkedQueue *queue = createLinkedQueue();
	int expected[16];
	for(int i = 0; i < 16; i ++) {
		push_back(queue, i+1);
		expected[i] = i+1;
	}
	if (VERBOSE) printf("%i ", *peek_front(queue));
	if (*peek_front(queue) != 1) return ERR;
	int val;
	for(int i = 0; pop_front(queue, &val) == OK; i ++) {
		if (VERBOSE) printf("%i ", val);
		if (val != expected[i]) return ERR;
	}
	if(!is_empty(queue) && VERBOSE) {printf("Queue is empty not full?"); return ERR;}
	if(!is_empty(queue)) return ERR;
	free(queue);
	printf("Linked queue === PASS\n");
	return OK;
}

Result queueTest() {
	if(sequentialQueueTest() == ERR) return ERR;
	printf("\n");
	if(linkedQueueTest() == ERR) return ERR;
	return OK;
}

Result dequeueTest() {
	Dequeue *queue = createDequeue();
	push_front(queue, 2);
	push_front(queue, 1);
	push_front(queue, 0);
	push_back(queue, 3);
	push_back(queue, 4);
	push_back(queue, 5);
	if (VERBOSE) printf("%i %i\n", *peek_front(queue), *peek_back(queue)); // 0 5
	if(*peek_front(queue) != 0 || *peek_back(queue) != 5) return ERR;
	int val;
	int expected[6] = {0,1,2,5,4,3};
	for(int i = 0; i < 3; i ++) {
		pop_front(queue, &val);
		if (VERBOSE) printf("%i ", val); // 0 1 2
		if(val != expected[i]) return ERR;
	}
	for(int i = 3; pop_back(queue, &val) == OK; i++) { // 5 4 3
		if (expected[i] != val) return ERR;
		if (VERBOSE) printf("%i ", val);
	} 
	if (!is_empty(queue) && VERBOSE) {printf("Queue is empty not full"); return ERR;}
	free(queue);
	printf("Dequeue === PASS\n");
	return OK;
}

Result binaryTreeTest() {
	bTree *tree = createBTree();
	int list[14] = {28,15,37,4,25,32,46,3,12,20,30,34,14,23};
	for(int i = 0; i < 14; i ++) {
 		addNode(tree, list[i]);
	}
	if (VERBOSE) printTree(tree);
	if (VERBOSE) printTree(tree, PRE_ORDER);
	if (VERBOSE) printTree(tree, POST_ORDER);
	bTreeNode *node;
	if (find(tree, 69, &node) == OK) return ERR;
	if (find(tree, 37, &node) == ERR) return ERR;
	bTreeNode *node2;
	if (findParent(tree,46, &node2) == ERR) return ERR;
	if (node2 != node) return ERR;
	if (find(tree, 23, &node) == ERR) return ERR;
	if (depth(tree, node) != 4) return ERR;
	if (treeHeight(tree) != 4) return ERR;
	if (treeSum(tree) != 323) return ERR;
	bTreePath path = traverseTree(tree);
	for(int i = 0; i < path.size; i ++) {
		path.list[i]->val++;
	}
	path = traverseTree(tree, PRE_ORDER);
	if (VERBOSE) printTree(tree, POST_ORDER);
	for(int i = 0; i < path.size; i ++) {
		path.list[i]->val--;
	}
	if (VERBOSE) printTree(tree);
	// if (deleteNode(tree, 3) == ERR) return ERR;
	// if (deleteNode(tree, 12) == ERR) return ERR;
	// if (deleteNode(tree, 4) == ERR) return ERR;
	if (deleteNode(tree, 15) == ERR) return ERR;
	find(tree, 14, &node);
	if (depth(tree, node) != 1) return ERR;
	if (VERBOSE) printTree(tree);
	free(tree);
	printf("Binary tree === PASS\n");
	return OK;
}

void treePrint(avlNode *root) {
	if(root == NULL) return;
	printf("%i {", root->val);
	treePrint(root->left);
	printf("} {");
	treePrint(root->right);
	printf("}");
}
void treePrint(avlTree *tree) {treePrint(tree->root);printf("\n");}

Result avlTreeTest() {
	avlTree *tree = createAvlTree();
	int list[6] = {1,2,5,6,4,3};
	for(int i = 0; i < 6; i ++) {
		if(addNode(tree, list[i]) == ERR) return ERR;
	}
	if(tree->root->val != 4) {
		if (VERBOSE) printf("Wrong root\n");
		return ERR;
	}
	if (VERBOSE) printTree(tree, PRE_ORDER);
	deleteNode(tree, 2);
	deleteNode(tree, 1);
	deleteNode(tree, 3);
	treePrint(tree);
	printf("AVL tree === PASS\n");
	return OK;
}

Result hashTest(HashTableType type) {
	HashTable *table = createHashTable(100, type);
	if(insert(table, 1) == ERR) {
		printf("Hash insert failed\n");
		return ERR;
	}
	if(insert(table, 3) == ERR) {
		printf("Hash insert failed\n");
		return ERR;
	}
	if(insert(table, 5) == ERR) {
		printf("Hash insert failed\n");
		return ERR;
	}
	if(VERBOSE) print(table);
	if(insert(table, collision(5, table->size)) == ERR) {
		printf("Cant insert duplicate\n");
		return ERR;
	}
	if(VERBOSE) print(table);
	if(remove(table, 3) == ERR) {
		printf("Hash remove failed\n");
		return ERR;
	}
	if(VERBOSE) print(table);
	if(search(table, 3) != NULL) {
		printf("Item is deleted\n");
		return ERR;
	}
	if(remove(table, 69) == OK) {
		if(VERBOSE) printf("Removed element that doesnt exist\n");
		return ERR;
	}
	printf("Hash === PASS\n");
	return OK;
}

Result heapTest() {
	int arr[10] = {10,12,9,78,33,21,35,29,5,8};
	Heap *heap = heapify(arr, 10, 12);
	print(heap);
	if(insert(heap, 69) == ERR) return ERR;
	if(insert(heap, 420) == ERR) return ERR;
	if(insert(heap, 69420) == OK) return OK;
	print(heap);
	int i;
	if(remove(heap, &i) == ERR) return ERR;
	if(i != 420) return ERR;
	if(!includes(heap, 69)) return ERR;
	if(includes(heap, 123)) return ERR;
	print(heap);
	printf("Heap === PASS\n");
	return OK;
}

Result fullTest() {
	printf("Running test suite\n-==-===-!==-===-==-\n\n");
	if (linkedListTest() == ERR) return ERR;
	printf("\n");
	if (doubleLinkedListTest() == ERR) return ERR;
	printf("\n");
	if (stackTest() == ERR) return ERR;
	printf("\n");
	if (queueTest() == ERR) return ERR;
	printf("\n");
	if (dequeueTest() == ERR) return ERR;
	printf("\n");
	if (binaryTreeTest() == ERR) return ERR;
	printf("\n");
	if (avlTreeTest() == ERR) return ERR;
	printf("\n");
	if (hashTest(OPEN) == ERR) return ERR;
	if (hashTest(CHAIN) == ERR) return ERR;
	if (hashTest(SCATTER) == ERR) return ERR;
	printf("\n");
	if (heapTest() == ERR) return ERR;
	printf("\n");
	return OK;
}