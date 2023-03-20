#pragma once
#include "utils.h"

typedef enum {
	OPEN,
	CHAIN,
	SCATTER
} HashTableType;

typedef struct _HashNode {
	int key;
	int hash;
	_HashNode *next;
} HashNode;

typedef struct {
	int key;
	int hash;
	int next;
} ScatterNode;

typedef struct {
	int size;
	void **table;
	HashTableType type;
	HashNode *deleted;
} HashTable;

int hash(int key);
int collision(int key, int size);

HashNode *createHashNode(int key);
void free(HashNode *node);
ScatterNode *createScatterNode(int key);
void free(ScatterNode *node);

HashTable *createHashTable(int size, HashTableType type);
void free(HashTable *table);
void print(HashTable *table);

Result insert(HashTable *table, int key);
Result remove(HashTable *table, int key);
void *search(HashTable *table, int key);