#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

int hash(int key) { // Returns a number from 0-999
	if (VERBOSE) printf("Key: %3i - ", key);
	unsigned int x = key;
	for(int i = 0; i < 5; i ++) { // Repeat
		if(x == 0) x += 1234; // Will colide with 1234
		for(int i = 1; x < 1000000;x*=(x+i++));
		while(x > 100000) { // lsb are somewhat predictable maybe?
			x >>= ((x%2)+1); // Might as well do some bitshifting
		}
		x %= 1000;
	// WE GO AGAIN!
	}
	if (VERBOSE) printf("Hash: %3i\n", x);
	return x;
}

int collision(int key, int size) {
	int h = hash(key)%size;
	if(VERBOSE) printf("Looking for key with hash: %i\n", h);
	for(int i = 0; i < 100*size; i ++) {
		if(i == key) continue;
		if(hash(i)%size == h) {
			if(VERBOSE) printf("Found collision! %i - %i\n", key, i);
			return i;
		}
	}
	return 0;
}

HashNode *createHashNode(int key) {
	HashNode *node = (HashNode*)malloc(sizeof(HashNode));
	node->key = key;
	node->hash = hash(key);
	node->next = NULL;
	return node;
}

void free(HashNode *node) {
	if(node == NULL) return;
	free(node->next);
	free((void*)node);
}

ScatterNode *createScatterNode(int key) {
	ScatterNode *node = (ScatterNode*)malloc(sizeof(ScatterNode));
	node->key = key;
	node->hash = hash(key);
	node->next = -1;
	return node;
}

void free(ScatterNode *node) {
	if(node == NULL) return;
	free((void*)node);
}

HashTable *createHashTable(int size, HashTableType type) {
	HashTable *table = (HashTable*)malloc(sizeof(HashTable));
	table->size = size;
	table->table = (void**)malloc(size*sizeof(void*));
	table->deleted = createHashNode(-1);
	for(int i = 0; i < size; i ++) {
		table->table[i] = NULL;
	}
	table->type = type;
	return table;
}

void free(HashTable *table) {
	for(int i = 0; i < table->size; i ++) {
		free(table->table[i]);
	}
	free(table->deleted);
	free(table->table);
	free((void*)table);
}

void print(HashTable *table) {
	printf("Table: \n");
	for(int i = 0; i < table->size; i ++) {
		if(table->table[i] != NULL) {
			if(table->table[i] == table->deleted) {
				printf("Index %3i: Deleted\n", i);
			} else {
				printf("Index %3i: %i\n", i, ((HashNode*)(table->table[i]))->key);
			}
		}
	}
}

Result insertOpen(HashTable *table, int key) {
	HashNode *node = createHashNode(key);
	int index = node->hash % table->size;
	if(table->table[index] == NULL || table->table[index] == table->deleted) {
		table->table[index] = node;
		return OK;
	}
	int newIndex = index;
	while(table->table[newIndex] != NULL && table->table[newIndex] != table->deleted) {
		newIndex++;
		if(newIndex >= table->size) {
			newIndex = 0;
		} else if (newIndex == index) {
			return ERR;
		}
	}
	table->table[newIndex] = node;
	return OK;
}

Result insertChain(HashTable *table, int key) {
	HashNode *node = createHashNode(key);
	int index = node->hash % table->size;
	node->next = (HashNode*)table->table[index];
	table->table[index] = node;
	return OK;
}

Result insertScatter(HashTable *table, int key) {
	HashNode *node = createHashNode(key);
	int index = node->hash % table->size;
	if(table->table[index] == NULL || table->table[index] == table->deleted) {
		table->table[index] = node;
		return OK;
	}
	int newIndex = index;
	while(table->table[newIndex] != NULL && table->table[newIndex] != table->deleted) {
		newIndex++;
		if(newIndex >= table->size) {
			newIndex = 0;
		} else if (newIndex == index) {
			return ERR;
		}
	}
	table->table[newIndex] = (void*)node;
	((ScatterNode*)(table->table[index]))->next = newIndex;
	return OK;
}

Result insert(HashTable *table, int key) {
	switch(table->type) {
		case OPEN:
			return insertOpen(table, key);
		break;
		case CHAIN:
			return insertChain(table, key);
		break;
		default: // Scatter
			return insertScatter(table, key);
		break;
	}
}

Result deleteOpen(HashTable *table, int key) {
	HashNode *node = (HashNode*)search(table, key);
	if(node == NULL) return ERR;

	int index = node->hash % table->size;
	int newIndex = index;
	while(table->table[newIndex] != NULL && table->table[newIndex] != table->deleted) {
		if(table->table[newIndex] == NULL) return ERR;
		if(((HashNode*)(table->table[newIndex]))->key == key) {
			table->table[newIndex] = table->deleted; // Mark as deleted
		}
		newIndex++;
		if(newIndex >= table->size) {
			newIndex = 0;
		} else if (newIndex == newIndex -1) {
			return ERR;
		}
	}
	free(node);
	return OK;
}

Result deleteChain(HashTable *table, int key) {
	HashNode *node = (HashNode*)search(table, key);
	if(node == NULL) return ERR;

	// Remove item from LL
	int index = node->hash % table->size;
	HashNode **pNode = (HashNode**)(&(table->table[index]));
	if(*pNode == NULL) return ERR;
	
	while((*pNode)->key != key) {
		pNode = &((*pNode)->next);
		if(*pNode == NULL) return ERR; // Not found
	}
	*pNode = (*pNode)->next;

	node->next = NULL;
	free(node);
	return OK;
}

Result deleteScatter(HashTable *table, int key) {
	ScatterNode *node = (ScatterNode*)search(table, key);
	if(node == NULL) return ERR;

	// Remove item from LL
	int index = node->hash % table->size;
	int newIndex = index;
	if(table->table[newIndex] == NULL) return ERR; 
	int follower = -1;
	while(((ScatterNode*)(table->table[newIndex]))->key != key) {
		newIndex = ((ScatterNode*)(table->table[newIndex]))->next;
		if(newIndex == -1) return ERR; // Not found
		follower = newIndex;
	}
	if(follower != -1) {
		((ScatterNode*)(table->table[follower]))->next = ((ScatterNode*)(table->table[newIndex]))->next;
	}
	table->table[newIndex] = NULL;
	
	free(node);
	return OK;
}


Result remove(HashTable *table, int key) {
	switch(table->type) {
		case OPEN:
			return deleteOpen(table, key);
		break;
		case CHAIN:
			return deleteChain(table, key);
		break;
		default: // Scatter
			return deleteScatter(table, key);
		break;
	}
}

void *searchOpen(HashTable *table, int key) {
	int index = hash(key) % table->size;
	int newIndex = index;
	while(table->table[newIndex] != NULL && table->table[newIndex] != table->deleted) {
		if(table->table[newIndex] != NULL && ((ScatterNode*)(table->table[newIndex]))->key == key) {
			return table->table[newIndex];
		}
		newIndex++;
		if(newIndex >= table->size) {
			newIndex = 0;
		} else if (newIndex == index) {
			return NULL; // Full and not there
		}
	}
	return NULL; // Not there
}

void *searchChain(HashTable *table, int key) {
	int index = hash(key) % table->size;
	HashNode *head = (HashNode*)table->table[index];
	while(head != NULL) {
		if(head->key == key) return head;
		head = head->next;
	}
	return NULL; // Not there
}

void *searchScatter(HashTable *table, int key) {
	int index = hash(key) % table->size;
	while(table->table[index] != NULL) {
		if(((ScatterNode*)(table->table[index]))->key == key) return table->table[index];
		index = ((ScatterNode*)(table->table[index]))->next;
	}
	return NULL; // Not there
}

void *search(HashTable *table, int key) {
	switch(table->type) {
		case OPEN:
			return searchOpen(table, key);
		break;
		case CHAIN:
			return searchChain(table, key);
		break;
		default: // Scatter
			return searchScatter(table, key);
		break;
	}
}
