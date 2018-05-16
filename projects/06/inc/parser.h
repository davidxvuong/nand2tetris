#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "symbol_table.h"
#include "hack_isa.h"
//TODO: remove include statement
#include <stdio.h>

uint16_t parse_instruction(char* instruction);
void parse_labels(char* instruction, int instruction_num);
bool is_instruction(char* instruction);

#endif