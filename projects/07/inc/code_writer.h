#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include "vm_info.h"

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

#endif