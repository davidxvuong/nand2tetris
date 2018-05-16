#include "parser.h"

uint16_t parse_instruction(char* instruction) {
	return 0;
}

void parse_labels(char* instruction, int instruction_num) {

}

bool is_instruction(char* instruction) {
	int index;
	char* ptr_to_index;

	ptr_to_index = strchr(instruction, '\n');
	index = (int)(ptr_to_index - instruction);

	if (index <= 1) {
		//empty line
		return false;
	}

	ptr_to_index = strstr(instruction, "//");
	index = (int)(ptr_to_index - instruction);

	if (index == 0) {
		//comment to start off the line
		return false;
	}

	return true;
}