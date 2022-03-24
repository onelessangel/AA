// Copyright 2021 Teodora Stroe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commands.h"
#include "messages.h"

// adds a new integer element to the hashtable
void insert_int(FILE *file, hashtable_t *ht, int element)
{
	if (ht_has_key(ht, &element)) {
		insert_error_int(file, element);
		return;
	}

	int size = sizeof(element);

	ht_put(ht, &element, size, &element, size);
	insert_success_int(file, element);
}

// adds a new string element to the hashtable
void insert_string(FILE *file, hashtable_t *ht, char *element)
{
	if (ht_has_key(ht, element)) {
		insert_error_string(file, element);
		return;
	}

	int size = strlen(element) + 1;

	ht_put(ht, element, size, element, size);
	insert_success_string(file, element);
}

// deletes an existing integer element from the hashtable
void delete_int(FILE *file, hashtable_t *ht, int element)
{
	if (!ht_has_key(ht, &element)) {
		delete_error_int(file, element);
		return;
	}

	ht_remove_entry(ht, &element);
	delete_success_int(file, element);
}

// deletes an existing string element from the hashtable
void delete_string(FILE *file, hashtable_t *ht, char *element)
{
	if (!ht_has_key(ht, element)) {
		delete_error_string(file, element);
		return;
	}

	ht_remove_entry(ht, element);
	delete_success_string(file, element);
}

// changes an existing integer element to a new integer element in the hashtable
void modify_int(FILE *file, hashtable_t *ht, int old_element, int new_element)
{
	if (!ht_has_key(ht, &old_element) || ht_has_key(ht, &new_element)) {
		modify_error_int(file, old_element);
		return;
	}

	int size = sizeof(new_element);

	ht_modify_entry(ht, &old_element, &new_element, size, &new_element, size);
	modify_success_int(file, old_element, new_element);
}

// changes an existing string element to a new string element in the hashtable
void modify_string(FILE *file, hashtable_t *ht, char *old_element, 
				   char *new_element)
{
	if (!ht_has_key(ht, old_element) || ht_has_key(ht, new_element)) {
		modify_error_string(file, old_element);
		return;
	}

	int size = strlen(new_element) + 1;

	ht_modify_entry(ht, old_element, new_element, size, new_element, size);
	modify_success_string(file, old_element, new_element);
}