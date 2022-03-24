// Copyright 2021 Teodora Stroe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

//  creates new generic linked list
/// @data_size: the size in bytes of the data contained in the list
linked_list_t *ll_create(unsigned int data_size)
{
	linked_list_t *linkedList = malloc(sizeof(*linkedList));
	DIE(NULL == linkedList, "list malloc failed");

	linkedList->head = NULL;
	linkedList->data_size = data_size;
	linkedList->size = 0;

	return linkedList;
}

//  creates new node containing given data
/// @new_data: the data to be contained by the node
/// @data_size: the size in bytes of the data aforementioned
ll_node_t *create_node(const void *new_data, unsigned int data_size)
{
	ll_node_t *node;

	node = malloc(sizeof(*node));
	DIE(NULL == node, "node malloc failed");

	node->data = malloc(data_size);
	DIE(NULL == node->data, "node data malloc failed");

	memcpy(node->data, new_data, data_size);

	return node;
}

//  returns the node located on the nth position in given list, going clockwise
/// @list: the list in which the search is made
/// @n: the desired position 
ll_node_t *get_nth_node(linked_list_t *list, unsigned int n)
{
	ll_node_t *node = list->head;

	n = MIN(n, list->size - 1);

	for (unsigned int i = 0; i < n; i++) {
		node = node->next;
	}

	return node;
}

//  frees given node
/// @node: the node to be freed
void free_node(ll_node_t *node)
{
	free(node->data);
	free(node);
}

//  adds node on the nth position in given list
/// @list: the list in which the data is added
/// @n; the position on which the new data is to be added
/// @new_data: the data to be added to the list
void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data)
{
	if (!list) {
		return;
	}

	ll_node_t *new_node = create_node(new_data, list->data_size);

	if (!n || list->size == 0) {
		new_node->next = list->head;
		list->head = new_node;
	} else {
		ll_node_t *prev_node = get_nth_node(list, n - 1);
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}
	list->size++;
}

//  removes node located on the nth position in list
/// @list: the list from which the removal takes place
/// @n: the position of the element which is to be deleted
ll_node_t *ll_remove_nth_node(linked_list_t *list, unsigned int n)
{
	ll_node_t *removed_node;

	if (!list || !list->size) {
		return NULL;
	}

	n = MIN(list->size - 1, n);

	if (!n) {
		removed_node = list->head;
		list->head = list->head->next;
	} else {
		ll_node_t *prev_node = get_nth_node(list, n - 1);
		removed_node = prev_node->next;
		prev_node->next = removed_node->next;
	}
	list->size--;

	return removed_node;
}

// returns the size of the given list
unsigned int ll_get_size(linked_list_t *list)
{
	return list->size;
}

// frees the given linked list
void ll_free(linked_list_t **pp_list)
{
	if (!pp_list || !*pp_list) {
		return;
	}

	while ((*pp_list)->size) {
		free_node(ll_remove_nth_node(*pp_list, 0));
	}

	free(*pp_list);
	*pp_list = NULL;
}

// prints the list, if it contains integers - used for testing
void ll_print_int(linked_list_t *list)
{
	ll_node_t *node = list->head;
	for (unsigned int i = 0; i < list->size; i++) {
		printf("%d ", *(int *)node->data);
		node = node->next;
	}
	printf("\n");
}

// prints the list, if it contains strings - used for testing
void ll_print_string(linked_list_t *list)
{
	ll_node_t *node = list->head;
	for (unsigned int i = 0; i < list->size; i++) {
		printf("%s ", (char *)node->data);
		node = node->next;
	}
	printf("\n");
}
