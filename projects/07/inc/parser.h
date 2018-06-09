#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "uthash.h"
#include "vm_info.h"
#include <stdio.h>

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

//Structure for Hash Table
typedef struct {
	char* id;
	int value;
	UT_hash_handle hh;
} pair_t;

#ifndef VM_STRUCT
#define VM_STRUCT

typedef struct {
	int mem_segment;
	int value;
} mem_instr_t;

typedef struct {
	int instr_type;
	union {
		mem_instr_t* mem_instr_info;
		int logical_instr_info;
	};
} vm_instr_t;

#endif

vm_instr_t* parse_instruction(char* instr);
int run_regex(char* str, char* regex);
int get_mem_segment(char* str);
int get_mem_value(char* str);
char* copy_string(char* str);

void initialize_parser_hash_table();
void kill_parser_hash_table();
void add_parser_value(char* id, int value);
int find_parser_value(char* id);
void remove_whitespaces(char* str);

#endif