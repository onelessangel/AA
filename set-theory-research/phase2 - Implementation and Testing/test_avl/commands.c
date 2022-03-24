// Copyright 2021 Teodora Stroe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commands.h"
#include "messages.h"

// adds a new integer element to the avl tree
void insert_int(FILE *file, avl_tree_t *tree, int element)
{
	if (avl_has_key(tree, &element)) {
		insert_error_int(file, element);
		return;
	}

	int size = sizeof(element);

	avl_insert(tree, &element, size);
	insert_success_int(file, element);
}

// adds a new string element to the avl tree
void insert_string(FILE *file, avl_tree_t *tree, char *element)
{
	if (avl_has_key(tree, element)) {
		insert_error_string(file, element);
		return;
	}

	int size = strlen(element) + 1;

	avl_insert(tree, element, size);
	insert_success_string(file, element);
}

// deletes an existing integer element from the avl tree
void delete_int(FILE *file, avl_tree_t *tree, int element)
{
	if (!avl_has_key(tree, &element)) {
		delete_error_int(file, element);
		return;
	}

	int size = sizeof(element);

	avl_delete(tree, &element);
	delete_success_int(file, element);
}

// deletes an existing string element from the avl tree
void delete_string(FILE *file, avl_tree_t *tree, char *element)
{
	if (!avl_has_key(tree, element)) {
		delete_error_string(file, element);
		return;
	}

	int size = strlen(element) + 1;

	avl_delete(tree, element);
	delete_success_string(file, element);
}

// changes an existing integer element to a new integer element in the avl tree
void modify_int(FILE *file, avl_tree_t *tree, int old_element, int new_element)
{
	if (!avl_has_key(tree, &old_element) ||
		 avl_has_key(tree, &new_element)) {
		modify_error_int(file, old_element);
		return;
	}

	int size = sizeof(new_element);

	avl_modify(tree, &old_element, &new_element, size);
	modify_success_int(file, old_element, new_element);
}

// changes an existing string element to a new string element in the avl tree
void modify_string(FILE *file, avl_tree_t *tree, char *old_element,
				   char *new_element)
{
	if (!avl_has_key(tree, old_element) ||
		 avl_has_key(tree, new_element)) {
		modify_error_string(file, old_element);
		return;
	}

	int size = strlen(new_element) + 1;

	avl_modify(tree, old_element, new_element, size);
	modify_success_string(file, old_element, new_element);
}