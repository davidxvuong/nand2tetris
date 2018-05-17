#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
//TODO: remove include statement
#include <stdio.h>
#include <string.h>

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

#ifndef SYMBOL_TABLE_INIT
#define SYMBOL_TABLE_INIT

#define SCREEN 		16384
#define KBD 		24576
#define SP 			0
#define LCL 		1
#define ARG 		2
#define THIS 		3
#define THAT		4

#endif

typedef struct map {
	char* key;
	int value;
	struct map* next;
} map_t;

typedef struct table {
	int size;
	map_t* head;
} table_t;

table_t* symbol_table;

void initialize_table();
void kill_table();
void print_table();
void insert(char* key, int value);
int lookup(const char* key);

#endif