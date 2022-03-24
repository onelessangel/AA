// Copyright 2021 Teodora Stroe
#ifndef AVL_H_
#define AVL_H_

typedef struct avl_node avl_node_t;
struct avl_node {
	void *data;
	int height;
	struct avl_node *left, *right;
};

typedef struct avl_tree avl_tree_t;
struct avl_tree {
	avl_node_t *root;
	int(*cmp)(const void*, const void*);
};

avl_tree_t *avl_create(int (*cmp)(const void*, const void*));

void avl_free(avl_tree_t *tree);

void avl_insert(avl_tree_t *tree, void *value, size_t data_size);

int get_key(avl_tree_t *tree, void *value);

int avl_has_key(avl_tree_t *tree, void *value);

avl_node_t *max_element(avl_tree_t *tree);

void avl_delete(avl_tree_t *tree, void *value);

void avl_modify(avl_tree_t *tree, void *value, void *new_value, 
				size_t data_size);

// compare functions
int compare_ints(void *a, void *b);

int compare_strings(void *a, void *b);

void inorder_traversal(avl_node_t *node);

#endif // AVL_H_
