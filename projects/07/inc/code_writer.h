#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vm_info.h"

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

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

int jump_counter;

char* generate_hack_instruction(vm_instr_t* instr, char* filename);
void initialize_jump_counter();

//helper functions
char* push_command(int val, char* segPtr);
char* pop_command(int val, char* segPtr);
char* cmp_branch_command(int counter, char* jump_type);
char* double_operand_command(char* operand);

char* push_local_command(int val);
char* pop_local_command(int val);
char* push_argument_command(int val);
char* pop_argument_command(int val);
char* push_this_command(int val);
char* pop_this_command(int val);
char* push_that_command(int val);
char* pop_that_command(int val);
char* push_const_command(int val);
char* push_static_command(int val, char* filename);
char* pop_static_command(int val, char* filename);
char* push_temp_command(int val);
char* pop_temp_command(int val);
char* push_pointer_command(int val);
char* pop_pointer_command(int val);
char* add_command();
char* sub_command();
char* neg_command();
char* eq_command(int counter);
char* gt_command(int counter);
char* lt_command(int counter);
char* and_command();
char* or_command();
char* not_command();

#endif