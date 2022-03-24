// Copyright 2021 Teodora Stroe
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "treap.h"

// compare functions
int compare_ints(void *a, void *b)
{
    int *int_a = (int *)a;
    int *int_b = (int *)b;

    if ((*int_a) > (*int_b)) {
        return 1;
    } else if ((*int_a) < (*int_b)) {
        return -1;
    }

    return 0;
}

int compare_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

//  creates the Treap
/// @cmp: the function that compares data in the Treap
Treap_tree *treap_create(int (*cmp)(void*, void*))
{
	srand(time(NULL));
	Treap_tree *tree = malloc(sizeof(Treap_tree));
	tree->compare = cmp;
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	return tree;
}

//  frees subtree recursively, starting from given node
/// @node: node from which the functions starts
void node_free(Node **node)
{
	if (!(*node)) {
		return;
	}

	node_free(&(*node)->left);
	node_free(&(*node)->right);

	free((*node)->data);
	free(*node);
}

// frees tree, starting from the root node
void treap_free(Treap_tree *tree)
{
	if (tree->root != NULL) {
		node_free(&tree->root);
	}
	free(tree);
}

//  creates a node
/// @value: the value to be inserted into the node
/// @data_size: the size in bytes of the above value
Node *node_create(void *value, int data_size)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}
	node->data = malloc(data_size);

	// byte by byte copy of the value to the current node
	for (int i = 0; i < data_size; ++i) {
		*(char*)(node->data + i) = *(char*)(value + i);
	}

	// the leaf nodes have 0 height
	node->priority = rand() % MAX_PRIORITY;
	node->left = NULL;
	node->right = NULL;

	return node;
}

// the NULL nodes have a -1 priority to retain the max-heap property
int priority(Node *node)
{
	if (node == NULL) {
		return -1;
	}
	return node->priority;
}

//  Rotate node to the right

//       node  			    lson
//      /    \			   /    \
//    lson    y    --->    x    node
//    /  \     		           /   \
//   x   lrson                lrson  y
void rotate_right(Node **node)
{
	Node *lson;

	lson = (*node)->left;
	(*node)->left = lson->right;
	lson->right = *node;
	*node = lson;
}

//  Rotate node to the left

//      node  			    rson
//     /    \			   /    \
//    x     rson    --->  node    y
//          /   \		 /   \
//        rlson  y       x   rlson
void rotate_left(Node **node)
{
	Node *rson;

	rson = (*node)->right;
	(*node)->right = rson->left;
	rson->left = *node;
	*node = rson;
}

//  inserts data into the Treap
/// @node: the root of the current subtree used in the recursive traversal
/// @value: the data to be added into the Treap
/// @data_size: the size of the above data in bytes
/// @compare: the function that compares data in the Treap
void treap_insert(Node **node, void* value, int data_size,
				  int (*compare)(void*, void*))
{
	if (!(*node)) {
		*node = node_create(value, data_size);
		return;
	}

	int priority_child, priority_node;

	if (compare(value, (*node)->data) < 0) {
		treap_insert(&(*node)->left, value, data_size, compare);

		priority_child = priority((*node)->left);
		priority_node = priority(*node);

		if (priority_child > priority_node) {
			rotate_right(node);
		}
	} else {
		treap_insert(&(*node)->right, value, data_size, compare);

		priority_child = priority((*node)->right);
		priority_node = priority(*node);

		if (priority_child > priority_node) {
			rotate_left(node);
		}
	}
}

//  deletes a value from the Treap
/// @node: the root of the current subtree used in the recursive traversal
/// @value: the data to be deleted from the Treap
/// @data_size: the size of the above data in bytes
/// @compare: the function that compares data in the Treap
void treap_delete(Node **node, void *value, int data_size,
				  int (*compare)(void*, void*))
{
	if (!(*node)) {
		return;
	}

	int priority_child_left, priority_child_right;

	if (compare(value, (*node)->data) < 0) {
		treap_delete(&(*node)->left, value, data_size, compare);
	} else if (compare(value, (*node)->data) > 0) {
		treap_delete(&(*node)->right, value, data_size, compare);
	} else if (!(*node)->left && !(*node)->right) {
		node_free(node);
		*node = NULL;
	} else {
		priority_child_left = priority((*node)->left);
		priority_child_right = priority((*node)->right);

		if (priority_child_left > priority_child_right) {
			rotate_right(node);
		} else {
			rotate_left(node);
		}

		treap_delete(node, value, data_size, compare);
	}
}

//  finds a value in a Treap
/// @return: 1 if the value is in the Treap; NULL otherwise
void *get_key(Node *node, void *value, int data_size,
			  int (*compare)(void*, void*))
{
	if (!node) {
		return NULL;
	}

	if (compare(value, node->data) < 0) {
		return get_key(node->left, value, data_size, compare);
	}

	if (compare(value, node->data) > 0) {
		return get_key(node->right, value, data_size, compare);
	}

	return value;
}

//  finds a key in a Treap
/// @return: 1 if the key exists in the Treap; 0 otherwise
int treap_has_key(Treap_tree *tree, void *key, int size)
{
	return get_key(tree->root, key, size, tree->compare) ? 1 : 0;
}

//  modifies a value from the Treap
/// @node: the root node of the Treap
/// @value: data to be modified from the Treap
/// @data_size: the size of the above data in bytes
/// @new_node: the root of the current subtree used in the recursive traversal
/// @new_value: the new data in which the existing one has to be modified into
/// @new_data_size: the size of the above data in bytes
/// @compare: the function that compares data in the Treap
void treap_modify(Node **node, void *value, int data_size, 
				  Node **new_node, void *new_value, int new_data_size,
				  int (*compare)(void*, void*))
{
	if (treap_has_key) {
		treap_delete(node, value, data_size, compare);
		treap_insert(new_node, new_value, new_data_size, compare);
	}
}


//  checks if a tree respects the Treap properties - used for testing
/// @node: the current node in the recursive traversal
/// @compare: the function that compares data in the Treap
/// @return: number of nodes if the tree is a Treap, a negative value otherwise
int check_treap(Node *node, int (*compare)(void*, void*))
{
	if (node == NULL) {
		return 0;
	} else if (node->left == NULL && node->right == NULL) {
		return 1;
	} else if (node->left == NULL) {
		if (priority(node) >= priority(node->right) &&
			compare(node->data, node->right->data) <= 0) {
			return 1 + check_treap(node->right, compare);
		}
		return INT_MIN;
	} else if (node->right == NULL) {
		if (priority(node) >= priority(node->left) &&
			compare(node->data, node->left->data) >= 0) {
			return 1 + check_treap(node->left, compare);
		}
		printf("%d %d %d\n",
			   priority(node),
			   priority(node->left),
			   priority(node->right));
		return INT_MIN;
	} else {
		if (priority(node) >= priority(node->left) &&
			priority(node) >= priority(node->right) &&
			compare(node->data, node->left->data) >= 0 &&
			compare(node->data, node->right->data) <= 0) {
			return 1 + check_treap(node->left, compare) +
				   check_treap(node->right, compare);
		}
		printf("%d %d %d\n",
			   priority(node),
			   priority(node->left),
			   priority(node->right));
		return INT_MIN;
	}
}
