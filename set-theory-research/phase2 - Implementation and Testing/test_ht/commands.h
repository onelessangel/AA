// Copyright 2021 Teodora Stroe
#ifndef __COMMANDS_H_
#define __COMMANDS_H_

#include "../hashmap/Hashtable.h"

void get_command(char **line, char **cmd, char **arg1, char **arg2);

void insert_int(FILE *file, hashtable_t *ht, int element);

void insert_string(FILE *file, hashtable_t *ht, char *element);

void delete_int(FILE *file, hashtable_t *ht, int element);

void delete_string(FILE *file, hashtable_t *ht, char *element);

void modify_int(FILE *file, hashtable_t *ht, int old_element, int new_element);

void modify_string(FILE *file, hashtable_t *ht, char *old_element,
				   char *new_element);

#endif // __COMMANDS_H_