// Copyright 2021 Teodora Stroe
#ifndef __TREAP_H_
#define __TREAP_H_

#define MAX_PRIORITY 100

typedef struct Node
{
	void* data;
	int priority;

	struct Node *left, *right;
} Node;

typedef struct
{
	Node* root;
	int (*compare)(void*, void*);
} Treap_tree;

Treap_tree *treap_create(int (*cmp)(void*, void*));

void node_free(Node** node);

void treap_free(Treap_tree* tree);

Node *node_create(void* value, int data_size);

int priority(Node* node);

void rotate_right(Node** node);

void rotate_left(Node** node);

void treap_insert(Node** node, void* value, int data_size,
				  int (*compar)(void*, void*));

void treap_delete(Node** node, void* value, int data_size,
				  int (*compar)(void*, void*));

void *get_key(Node* node, void* value, int data_size,
			  int (*compar)(void*, void*));

int treap_has_key(Treap_tree *tree, void *key, int size);
			  
void treap_modify(Node **node, void *value, int data_size, 
				  Node **new_node, void *new_value, int new_data_size,
				  int (*compare)(void*, void*));

int check_treap(Node* node, int (*compar)(void*, void*));

// compare functions
int compare_ints(void *a, void *b);

int compare_strings(void *a, void *b);

#endif  // __TREAP_H_
