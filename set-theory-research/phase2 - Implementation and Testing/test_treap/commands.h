// Copyright 2021 Teodora Stroe
#ifndef __COMMANDS_H_
#define __COMMANDS_H_

#include "../treap/treap.h"

void insert_int(FILE *file, Treap_tree *tree, int element);

void insert_string(FILE *file, Treap_tree *tree, char *element);

void delete_int(FILE *file, Treap_tree *tree, int element);

void delete_string(FILE *file, Treap_tree *tree, char *element);

void modify_int(FILE *file, Treap_tree *tree, int old_element, int new_element);

void modify_string(FILE *file, Treap_tree *tree, char *old_element, 
				   char *new_element);

#endif // __COMMANDS_H_