#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <regex.h>
#include "symbol_table.h"
#include "hack_isa.h"
//TODO: remove include statement
#include <stdio.h>

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

#ifndef MACHINE_CODE_LENGTH
#define MACHINE_CODE_LENGTH 16
#endif

#ifndef HACK_INSTRUCTION_TYPE
#define HACK_INSTRUCTION_TYPE

#define HACK_A_INSTRUCTION 0
#define HACK_C_INSTRUCTION 1
#define HACK_LABEL 2
#define NOT_HACK_INSTRUCTION -1

#endif

#ifndef HACK_REGEX
#define HACK_REGEX

#define REGEX_A_INSTRUCTION "@\\w*"
#define REGEX_C_INSTRUCTION ".*=.*|(.*;\\w{3})"
#define REGEX_LABEL "(\\(\\w*|\\))"

#endif

char* translate_instruction(char* instruction);
void parse_labels(char* instruction, int instruction_num);
bool is_instruction(char* instruction);
void remove_comments(char* instruction);

//Helper functions
void trim(char* str);
int get_instruction_type(char* intruction);
int run_regex(char* instruction, char* regex_string);

#endif