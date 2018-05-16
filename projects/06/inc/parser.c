#include "parser.h"

uint16_t parse_instruction(char* instruction) {
	return 0;
}

void parse_labels(char* instruction, int instruction_num) {
	//Regex for matching brackets: (\(|\))
	regex_t regex;
	int reti;

	reti =regcomp(&regex, "(\\(\\w*|\\))", REG_EXTENDED);

	if (reti) {
		printf("Failed to compile regex\n");
	}

	reti = regexec(&regex, instruction, 0, NULL, 0);
	if (!reti) {
		//Found label. remove brackets and store data into symbol table
		char* pch = strtok(instruction, "()");

		if (pch != NULL) {
			insert(pch, instruction_num);
		}
	}
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

	//TODO: make sure that the line is either a label, A, or C instruction

	return true;
}

void remove_comments(char* instruction) {
	int index;
	char* ptr_to_index;

	ptr_to_index = strstr(instruction, "//");
	index = (int)(ptr_to_index - instruction);

	if (index > 0) {
		//Found comment after an instruction
		char* pch;
		pch = strtok (instruction,"//");

		if (pch != NULL) {
			// printf("[remove_comments] %s\n", pch);
			strcat(pch, "\n");
			strcpy(instruction, pch);
		}
	}

}

//Helper function
void trim(char *str)
{
    char *start, *end;

    /* Find first non-whitespace */
    for (start = str; *start; start++)
    {
        if (!isspace((unsigned char)start[0]))
            break;
    }

    /* Find start of last all-whitespace */
    for (end = start + strlen(start); end > start + 1; end--)
    {
        if (!isspace((unsigned char)end[-1]))
            break;
    }

    *end = 0; /* Truncate last whitespace */

    /* Shift from "start" to the beginning of the string */
    if (start > str)
        memmove(str, start, (end - start) + 1);
}