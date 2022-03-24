// Copyright 2021 Teodora Stroe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commands.h"
#include "utils.h"

#define MAX_BUCKETS	10
#define ARG_MAX		64
#define NMAX		7

int main()
{
	FILE *fin = fopen("test.in", "r");
	FILE *fout = fopen("test.out", "w");

	Treap_tree *tree;
	int n, type, arg1_int, arg2_int;
	char input_type[NMAX], cmd[NMAX];
	char arg1_string[ARG_MAX], arg2_string[ARG_MAX];

	fscanf(fin, "%d %s", &n, input_type);

	// creates the treap based on the input type
	if (!strcmp(input_type, "int")) {
		type = 0;
		tree = treap_create((int (*)(void*, void*))(compare_ints));
	} else {
		type = 1;
		tree = treap_create((int (*)(void*, void*))(compare_strings));
	}

	// reads the command and its arguments and calls the corresponding function
	for (int i = 0; i < n; ++i) {
		fscanf(fin, "%s", cmd);

		if (!type) {
			fscanf(fin, "%d", &arg1_int);
		} else {
			fscanf(fin, "%s", arg1_string);
		}

		if (!strcmp(cmd, "insert")) {
			if (!type) {
				insert_int(fout, tree, arg1_int);
			} else {
				insert_string(fout, tree, arg1_string);
			}
		} else if (!strcmp(cmd, "delete")) {
			if (!type) {
				delete_int(fout, tree, arg1_int);
			} else {
				delete_string(fout, tree, arg1_string);
			}
		} else if (!strcmp(cmd, "modify")) {
			if (!type) {
				fscanf(fin, "%d", &arg2_int);
				modify_int(fout, tree, arg1_int, arg2_int);
			} else {
				fscanf(fin, "%s", arg2_string);
				modify_string(fout, tree, arg1_string, arg2_string);
			}
		}
	}

	treap_free(tree);
	fclose(fin);
	fclose(fout);
	return 0;
}