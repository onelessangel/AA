// Copyright 2021 Teodora Stroe

void insert_success_int(FILE *file, int element);

void insert_success_string(FILE *file, char *element);

void insert_error_int(FILE *file, int element);

void insert_error_string(FILE *file, char *element);

void delete_success_int(FILE *file, int element);

void delete_success_string(FILE *file, char *element);

void delete_error_int(FILE *file, int element);

void delete_error_string(FILE *file, char *element);

void modify_success_int(FILE *file, int old_element, int new_element);

void modify_success_string(FILE *file, char *old_element, char *new_element);

void modify_error_int(FILE *file, int old_element);

void modify_error_string(FILE *file, char *old_element);