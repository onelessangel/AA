// Copyright 2021 Teodora Stroe
#include <stdio.h>

// prints '<element> added'
void insert_success_int(FILE *file, int element)
{
	fprintf(file, "%d added\n", element);
}

// prints '<element> added'
void insert_success_string(FILE *file, char *element)
{
	fprintf(file, "%s added\n", element);
}

// prints '<element> already exists'
void insert_error_int(FILE *file, int element)
{
	fprintf(file, "%d already exists\n", element);
}

// prints '<element> already exists'
void insert_error_string(FILE *file, char *element)
{
	fprintf(file, "%s already exists\n", element);
}

// prints '<element> deleted'
void delete_success_int(FILE *file, int element)
{
	fprintf(file, "%d deleted\n", element);
}

// prints '<element> deleted'
void delete_success_string(FILE *file, char *element)
{
	fprintf(file, "%s deleted\n", element);
}

// prints '<element> can't be deleted'
void delete_error_int(FILE *file, int element)
{
	fprintf(file, "%d can't be deleted\n", element);
}

// prints '<element> can't be deleted'
void delete_error_string(FILE *file, char *element)
{
	fprintf(file, "%s can't be deleted\n", element);
}

// prints '<old_element> modified into <new_element>'
void modify_success_int(FILE *file, int old_element, int new_element)
{
	fprintf(file, "%d modified into %d\n", old_element, new_element);
}

// prints '<old_element> modified into <new_element>'
void modify_success_string(FILE *file, char *old_element, char *new_element)
{
	fprintf(file, "%s modified into %s\n", old_element, new_element);
}

// prints '<old_element> can't be modified'
void modify_error_int(FILE *file, int old_element)
{
	fprintf(file, "%d can't be modified\n", old_element);
}

// prints '<old_element> can't be modified'
void modify_error_string(FILE *file, char *old_element)
{
	fprintf(file, "%s can't be modified\n", old_element);
}