// Copyright 2021 Teodora Stroe
#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "LinkedList.h"

typedef struct info info;
struct info {
	void *key;
	void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t {
	linked_list_t **buckets;  // array of liked list
	unsigned int size; // number of nodes in all of the buckets
	unsigned int hmax; // number of buckets
	unsigned int (*hash_function)(void*); // pointer to hash function
	int (*compare_function)(void*, void*); // pointer to compare function
};

hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
					   int (*compare_function)(void*, void*));

void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
			void *value, unsigned int value_size);

void *ht_get(hashtable_t *ht, void *key);

int ht_has_key(hashtable_t *ht, void *key);

void ht_remove_entry(hashtable_t *ht, void *key);

unsigned int ht_get_size(hashtable_t *ht);

unsigned int ht_get_hmax(hashtable_t *ht);

void ht_modify_entry(hashtable_t *ht, void *key, void *new_key, 
					 unsigned int new_key_size, void *value, 
					 unsigned int value_size);

void ht_free(hashtable_t *ht);

// compare functions
int compare_function_ints(void *a, void *b);

int compare_function_strings(void *a, void *b);

// hash functions
unsigned int hash_function_int(void *a);

unsigned int hash_function_string(void *a);

#endif  // HASHTABLE_H_
