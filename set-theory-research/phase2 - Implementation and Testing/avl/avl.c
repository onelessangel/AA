// Copyright 2021 Teodora Stroe
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "avl.h"

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

//  creates AVL tree
/// @cmp: the function that compares data in the AVL tree
avl_tree_t *avl_create(int (*cmp)(const void*, const void*))
{
	avl_tree_t *tree = malloc(sizeof(*tree));
	if (!tree)
		return NULL;
	
	tree->cmp = cmp;
	tree->root = NULL;

	return tree;
}

//  frees subtree recursively, starting from given node
/// @node: node from which the functions starts
void node_free(avl_node_t **node) {

	if (!(*node)) {
		return;
	}

	if ((*node)->left) {
		node_free(&(*node)->left);
	}

	if ((*node)->right) {
		node_free(&(*node)->right);
	}

	avl_node_t *temp = (*node);

	if (!(*node)->left && !(*node)->right) {
		free(temp->data);
		free(temp);
		(*node) = NULL;
		return;
	}
}

//  frees node
/// @node: node to be freed
void free_node(avl_node_t *node) {
	free(node->data);
	free(node);
}

// frees tree, starting from the root node
void avl_free(avl_tree_t *tree)
{
	if (tree->root)
		node_free(&tree->root);
	free(tree);
}

static int __max(int a, int b)
{
	return a > b ? a : b;
}

//  creates an AVL node
/// @value: the value to be inserted into the node
/// @data_size: the size in bytes of the above value
static avl_node_t *__node_create(void *value, size_t data_size)
{
	avl_node_t *node = malloc(sizeof(*node));
	if (node == NULL)
		return NULL;

	node->data = malloc(data_size);
	if (!node->data) {
		free(node);
		return NULL;
	}

	memcpy(node->data, value, data_size);

	/* Leaf nodes have a height of 0. */
	node->height = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}

// NULL nodes have a height of -1 in order for the rule below to hold:
// node->height = 1 + max(node->left->height, nod->right->height)
static int __height(avl_node_t *node)
{
	return node ? node->height : -1;
}

//  Rotate node to the right

//       node  			    lson
//      /    \			   /    \ 
//    lson    y    --->    x    node
//    /  \     		           /   \ 
//   x   lrson                lrson  y
static void __rotate_right(avl_node_t **node) {
	avl_node_t *lson = (*node)->left;
	avl_node_t *lrson = lson->right;
	avl_node_t *rson = (*node);

	(*node) = lson;
	(*node)->right = rson;
	(*node)->right->left = lrson;

	/* Fix height. */
	(*node)->right->height = 1 + __max(__height((*node)->right->left),
		__height((*node)->right->right));
	(*node)->height = 1 + __max(__height((*node)->left),
		__height((*node)->right));

}

//  Rotate node to the left

//      node  			    rson
//     /    \			   /    \ 
//    x     rson    --->  node    y
//          /   \		 /   \
//        rlson  y       x   rlson
static void __rotate_left(avl_node_t **node) {
	avl_node_t *rson = (*node)->right;
	avl_node_t *rlson = rson->left;
	avl_node_t *lson = (*node);
	
	(*node) = rson;
	(*node)->left = lson;
	(*node)->left->right = rlson;

	// Fix height.
	(*node)->left->height = 1 + __max(__height((*node)->left->left),
		__height((*node)->left->right));
	(*node)->height = 1 + __max(__height((*node)->left),
		__height((*node)->right));

}

// rebalances the AVL tree
static void __avl_fix(avl_node_t **node)
{
	if (__height((*node)->left) > __height((*node)->right) + 1 
			&& __height((*node)->left->left)
				>= __height((*node)->left->right)) {
		
		//  RR rotation:
		
		//      node                  a
		//      /                    / \
		//     a          --->      b   node
		//    /
		//   b
		
		__rotate_right(node);
	} else if (__height((*node)->right) > __height((*node)->left) + 1 
			&& __height((*node)->right->right)
				>= __height((*node)->right->left)) {

		//  LL rotation:
		
		//      node                a
		//         \               / \
		//          a     --->  node  b
		//           \ 
		//            b
		
		__rotate_left(node);
	} else if (__height((*node)->left) > __height((*node)->right) + 1 
			&& __height((*node)->left->left)
				< __height((*node)->left->right)) {

		//  LR rotation:

		//      node                node               b
		//      /        left       /      right      / \
		//     a         --->      b        --->     a   node
		//      \                 /
		//       b               a
		
		__rotate_left(&(*node)->left);
		__rotate_right(node);
	} else if (__height((*node)->right) > __height((*node)->left) + 1 
			&& __height((*node)->right->right)
				< __height((*node)->right->left)) {

		//  RL rotation:

		//      node                node                  b
		//         \      right        \       left      / \
		//          a      --->         b       --->   node a
		//         /                     \
		//        b                       a
		
		__rotate_right(&(*node)->right);
		__rotate_left(node);
	}
}

//  inserts data into an AVL subtree
/// @node: the root of the current subtree
/// @value: the data to be added into the subtree
/// @data_size: the size of the above data in bytes
/// @cmp: the function that compares data in the AVL tree
static void __avl_insert(avl_node_t **node, void *value, size_t data_size,
						 int (*cmp)(const void*, const void*))
{
	if (!(*node)) {
        *node = __node_create(value, data_size);
        return;
    }

	int rc = cmp(value, (*node)->data);

	if (rc < 0) {
		__avl_insert(&(*node)->left, value, data_size, cmp);
	} else if (rc > 0) {
		__avl_insert(&(*node)->right, value, data_size, cmp);
	}

	(*node)->height = 1 + __max(__height((*node)->left),
								__height((*node)->right));
	__avl_fix(node);
}

//  inserts data into the AVL tree
/// @node: the tree to which to add the data
/// @value: the data to be added into the AVL tree
/// @data_size: the size of the above data in bytes
void avl_insert(avl_tree_t *tree, void *value, size_t data_size)
{
	if (tree)
		__avl_insert(&tree->root, value, data_size, tree->cmp);
}

//  finds a value in an AVL tree
/// @node: the root of the current subtree
/// @value: the data to be searched in the subtree
/// @cmp: the function that compares data in the AVL tree
/// @return: 1 if the value is in the tree; 0 otherwise
static int __get_key(avl_node_t *node, void *value,
					 int (*cmp)(const void*, const void*))
{
	if (!node) {
        return 0;
    }

	int rc = cmp(value, node->data);

	if (rc < 0) {
        return __get_key(node->left, value, cmp);
    } else if (rc > 0) {
        return __get_key(node->right, value, cmp);
    }

    return 1;
}

//  finds a value in an AVL tree
/// @return: 1 if the value is in the tree; 0 otherwise
int get_key(avl_tree_t *tree, void *value)
{
	return tree ? __get_key(tree->root, value, tree->cmp) : 0;
}

static avl_node_t *__max_with_parent(avl_node_t *node, avl_node_t **parent)
{
	if (!node->right) {
		return node;
	}

	*parent = node;

	return __max_with_parent(node->right, parent);
}

static avl_node_t *__max_element(avl_node_t *node)
{
	return node->right ? __max_element(node->right) : node;
}

// retrieves the maximum element from an AVL tree
avl_node_t *max_element(avl_tree_t *tree)
{
	return tree && tree->root ? __max_element(tree->root) : NULL;
}

//  deletes a value from an AVL subtree
/// @node: the root of the current subtree
/// @value: the data to be deleted from the AVL tree
/// @cmp: the function that compares data in the AVL tree
static void __avl_delete(avl_node_t **node, void *value,
	int (*cmp)(const void*, const void*))
{
	if (!(*node)) {
		return;
	}

	avl_node_t *tmp, *parent = NULL, *temp;
	int rc = cmp(value, (*node)->data);

	if (rc < 0) {
		__avl_delete(&(*node)->left, value, cmp);
	} else if (rc > 0) {
		__avl_delete(&(*node)->right, value, cmp);
	} else {
		if (!(*node)->left && !(*node)->right) {  // node is a leaf
			free_node(*node);
			(*node) = NULL;
		} else if (!(*node)->right) {  // node has only left kid
			tmp = (*node)->left;
			free_node(*node);
			(*node) = tmp;
		} else if (!(*node)->left) {  // node has only right kid
			tmp = (*node)->right;
			free_node(*node);
			(*node) = tmp;
		} else {
			//node has both children
			tmp = __max_with_parent((*node)->left, &parent);
			temp = *node;
			if (tmp == (*node)->left) {
				tmp->right = (*node)->right;
				free_node(temp);
				(*node) = tmp;
			} else {
				parent->right = tmp->left;
				tmp->right = (*node)->right;
				tmp->left = (*node)->left;
				free_node(temp);
				(*node) = tmp;
			}			
		}
	}

	if (*node) {
		(*node)->height = 1 + __max(__height((*node)->left),
									__height((*node)->right));
		__avl_fix(node);
	}
}

/// deletes a value from the AVL tree 
/// @tree: the tree from which to delete the data
/// @value: the data to be deleted from the AVL tree
void avl_delete(avl_tree_t *tree, void *value)
{
	if (tree)
		__avl_delete(&tree->root, value, tree->cmp);
}

//  finds a key in an AVL tree
/// @return: 1 if the key exists in the tree; 0 otherwise
int avl_has_key(avl_tree_t *tree, void *value)
{
	if (get_key(tree, value)) {
		return 1;
	}

	return 0;
}

//  modifies a value from the AVL
/// @tree: the tree from which to modify the element
/// @value: the data to be modified from the AVL tree
/// @new_value: the new value in which the existing one has to be modified into
void avl_modify(avl_tree_t *tree, void *value, void *new_value, 
				size_t data_size)
{
	if (get_key(tree, value)) {
		avl_delete(tree, value);
		avl_insert(tree, new_value, data_size);
	}
}

// inorder traversal used for testing
void inorder_traversal(avl_node_t *node)
{
	if (!node)
		return;

	inorder_traversal(node->left);
	printf("%d ", *(int*)node->data);
	inorder_traversal(node->right);
}
