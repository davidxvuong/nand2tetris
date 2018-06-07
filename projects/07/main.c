#include <stdio.h>
#include <stdlib.h>
#include "inc/parser.h"

#define ARGV_INDEX 1

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif


int main(int argc, char* argv[]) {
	
	if (argc > 2) {
		printf("Invalid parameters\n");
		return -1;
	}

	FILE* fp = NULL;

	fp = fopen(argv[ARGV_INDEX], "r");

	if (fp == NULL) {
		printf("Unable to open file\n");
		return -1;
	}

	//initialize hash table
	initialize_parser_hash_table();

	while(!feof(fp)) {
		char* buf = (char*)(malloc(sizeof(char) * STRING_BUFFER));
		fgets(buf, STRING_BUFFER, fp);

		printf("%s", buf);
		vm_instr_t* parsed_instr = parse_instruction(buf);
		//Test
		if (parsed_instr != NULL) {
			printf("Instr Type: %d\n", parsed_instr -> instr_type);
			if (parsed_instr -> instr_type == ARITH_LOGIC_CMD) {
				printf("Command: %d\n", parsed_instr -> logical_instr_info);
			}
			else {
				printf("Mem Segment: %d\n", parsed_instr -> mem_instr_info -> mem_segment);
				printf("Value: %d\n", parsed_instr -> mem_instr_info -> value);
			}
		}
		else {
			printf("Not an instruction\n");
		}

		printf("\n");
	}

	fclose(fp);
	fp = NULL;

	kill_parser_hash_table();


	return 0;
}