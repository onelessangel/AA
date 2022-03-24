// Copyright 2021 Teodora Stroe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commands.h"
#include "messages.h"

// adds a new integer element to the treap
void insert_int(FILE *file, Treap_tree *tree, int element)
{
	int size = sizeof(element);

	if (treap_has_key(tree, &element, size)) {
		insert_error_int(file, element);
		return;
	}

	treap_insert(&tree->root, &element, size, tree->compare);
	insert_success_int(file, element);
}

// adds a new string element to the treap
void insert_string(FILE *file, Treap_tree *tree, char *element)
{
	int size = strlen(element) + 1;

	if (treap_has_key(tree, element, size)) {
		insert_error_string(file, element);
		return;
	}

	treap_insert(&tree->root, element, size, tree->compare);
	insert_success_string(file, element);
}

// deletes an existing integer element from the treap
void delete_int(FILE *file, Treap_tree *tree, int element)
{
	int size = sizeof(element);

	if (!treap_has_key(tree, &element, size)) {
		delete_error_int(file, element);
		return;
	}

	treap_delete(&tree->root, &element, size, tree->compare);
	delete_success_int(file, element);
}

// deletes an existing string element from the treap
void delete_string(FILE *file, Treap_tree *tree, char *element)
{
	int size = strlen(element) + 1;

	if (!treap_has_key(tree, element, size)) {
		delete_error_string(file, element);
		return;
	}

	treap_delete(&tree->root, element, size, tree->compare);
	delete_success_string(file, element);
}

// changes an existing integer element to a new integer element in the treap
void modify_int(FILE *file, Treap_tree *tree, int old_element, int new_element)
{
	int size_old = sizeof(old_element);
	int size_new = sizeof(new_element);

	if (!treap_has_key(tree, &old_element, size_old) || 
		 treap_has_key(tree, &new_element, size_new)) {
		modify_error_int(file, old_element);
		return;
	}

	treap_modify(&tree->root, &old_element, size_old,
				 &tree->root, &new_element, size_new, tree->compare);

	modify_success_int(file, old_element, new_element);
}

// changes an existing string element to a new string element in the treap
void modify_string(FILE *file, Treap_tree *tree, char *old_element, 
				   char *new_element)
{
	int size_old = strlen(old_element) + 1;
	int size_new = strlen(new_element) + 1;

	if (!treap_has_key(tree, old_element, size_old) || 
		 treap_has_key(tree, new_element, size_new)) {
		modify_error_string(file, old_element);
		return;
	}

	treap_modify(&tree->root, old_element, size_old,
				 &tree->root, new_element, size_new, tree->compare);
	modify_success_string(file, old_element, new_element);
}