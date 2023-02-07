#include "utils.h"
#include "linked_list.h"
#include "double_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "dequeue.h"
#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>

void linkedListBinarySearchTest() {
	int array[11] = {0,3,6,7,8,11,14,21,45,54,56};
	LinkedList *list = createLinkedList(array, 11);
	int val;
	printf("\n");
	for(val = 0; remove_head(list, &val) == OK; printf("%i ", val)) continue; // 0 3 6 7 ...
	list = createLinkedList(array, 11);
	if(linearSearch(list, 45) != binarySearch(list, 45) || linearSearch(array, 11, 45) != binarySearch(array, 11, 45)) {
	 printf("Uh oh linear and binary search are fighting again\n");
	}
	if(binarySearch(list, 0) == NULL || binarySearch(list, 56) == NULL || binarySearch(list, 9) != NULL) {
	 printf("Uh oh binary search is misbehaving\n");
	}
	if(binarySearch(array, 11, 0) == NULL || binarySearch(array, 11, 56) == NULL || binarySearch(array, 11, 9) != NULL) {
		printf("Smh my head\n");
	}
	if(arrayCompares != linkedCompares) {
		printf("I should drop out frfr no cap\n");
	}
	printf("\nArray compares:  %i\nLinked compares: %i\n", arrayCompares, linkedCompares);
}

void linkedListTest() {
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
	printf("%i ", val); // 69
	for(int i = 0; i < 3; i ++) {
		remove_head(list, &val);
		printf("%i ", val); // 0 1 2
	}
	while(remove_tail(list, &val) == OK) {
		printf("%i ", val); // 6 5 4 3
	}
	free(list);
	linkedListBinarySearchTest();
}


void doubleLinkedListTest() {
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
	printf("%i ", val); // 69
	for(int i = 0; i < 3; i ++) {
		remove_head(list, &val);
		printf("%i ", val); // 0 1 2
	}
	while(remove_tail(list, &val) == OK) {
		printf("%i ", val); // 6 5 4 3
	}
	printf("\n");
	LinkedList *slist = createLinkedList();
	insert_tail(slist, 5);
	insert_tail(slist, 4);
	insert_tail(slist, 3);
	insert_tail(slist, 2);
	insert_tail(slist, 1);
	list = createDoubleLinkedList(slist);
	free(slist);
	while(remove_head(list, &val)) {
		printf("%i ", val); // 5 4 3 2 1
	}
	free(list);
}

void sequentialStackTest() {
	SequentialStack *stack = createSequentialStack();
	for(int i = 0; i < 16; i ++) {
		push(stack, 16-i);
	}
	printf("%i ", *peek(stack)); // 1
	int val;
	while(pop(stack, &val) == OK) {
		printf("%i ", val); // 1 - 16
	}
	// Fill Test
	for(int i = 0; push(stack, i) == OK; i ++) continue;
	printf("\n%i ", *peek(stack)); // 99
	for(val = 0; pop(stack); val++);
	printf("\n%i\n", val); // 100
	free(stack);
}

void linkedStackTest() {
	LinkedStack *stack = createLinkedStack();
	for(int i = 0; i < 16; i ++) {
		push(stack, 16-i);
	}
	printf("%i ", *peek(stack)); // 1
	int val;
	while(pop(stack, &val) == OK) {
		printf("%i ", val); // 1 - 16
	}
	free(stack);
}

void stackTest() {
	sequentialStackTest();
	printf("\n");
	linkedStackTest();
}

void sequentialQueueTest() {
	SequentialQueue *queue = createSequentialQueue();
	if(!is_empty(queue)) printf("Queue is empty not full?");
	for(int i = 0; i < 16; i ++) {
		push_back(queue, i+1);
	}
	printf("%i ", *peek_front(queue)); // 1
	int val;
	while(pop_front(queue, &val) == OK) {
		printf("%i ", val); // 1 - 16
	}
	// Fill test
	printf("\n");
	for(int i = 0; push_back(queue, i+1) == OK; i ++) continue;
	for(val = 0; pop_front(queue, &val) == OK; printf("%i ", val)) continue;
	free(queue);
}

void linkedQueueTest() {
	LinkedQueue *queue = createLinkedQueue();
	for(int i = 0; i < 16; i ++) {
		push_back(queue, i+1);
	}
	printf("%i ", *peek_front(queue));
	int val;
	while(pop_front(queue, &val) == OK) {
		printf("%i ", val);
	}
	if(!is_empty(queue)) printf("Queue is empty not full?");
	free(queue);
}

void queueTest() {
	sequentialQueueTest();
	printf("\n");
	linkedQueueTest();
}

void dequeueTest() {
	Dequeue *queue = createDequeue();
	push_front(queue, 2);
	push_front(queue, 1);
	push_front(queue, 0);
	push_back(queue, 3);
	push_back(queue, 4);
	push_back(queue, 5);
	printf("%i %i\n", *peek_front(queue), *peek_back(queue)); // 0 5
	int val;
	for(int i = 0; i < 3; i ++) {
		pop_front(queue, &val);
		printf("%i ", val); // 0 1 2
	}
	for(val = 0; pop_back(queue, &val) == OK; printf("%i ", val)); // 5 4 3
	if (!is_empty(queue)) printf("Queue is empty not full");
	free(queue);
}

void fullTest() {
	linkedListTest();
	printf("\n");
	doubleLinkedListTest();
	printf("\n");
	stackTest();
	printf("\n");
	queueTest();
	printf("\n");
	dequeueTest();
}

int main() {
	fullTest();
	return 0;
}
