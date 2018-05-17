#include "parser.h"

char* translate_instruction(char* instruction) {
	char* result = (char*)(malloc(sizeof(char) * MACHINE_CODE_LENGTH));

	trim(instruction);
	int instruction_type = get_instruction_type(instruction);

	if (instruction_type == HACK_A_INSTRUCTION) {
		printf("%s", ++instruction);
	}
	else if (instruction_type == HACK_C_INSTRUCTION) {

	}

	return NULL;
}

void parse_labels(char* instruction, int instruction_num) {
	int regex_result = run_regex(instruction, "(\\(\\w*|\\))");

	if (!regex_result) {
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
     int index, i, j;

    index = 0;

    /* Find last index of whitespace character */
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }


    if(index != 0)
    {
        /* Shit all trailing characters to its left */
        i = 0;
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0'; // Make sure that string is NULL terminated
    }
}

int get_instruction_type(char* instruction) {
	/*
	Regex for A-instruction: @\w*
	Regex for C-instruction: .*=.*|(.*;\w{3})
	Regex for Destination labels: (\(\w*|\))

	*/

	//Determine what kind of instruction this is

	if (!run_regex(instruction, REGEX_A_INSTRUCTION)) {
		//A-instruction

		return HACK_A_INSTRUCTION;
	}
	else if (!run_regex(instruction, REGEX_C_INSTRUCTION)) {
		//C-instruction

		return HACK_C_INSTRUCTION;
	}
	else if (!run_regex(instruction, REGEX_LABEL)){
		//Label

		return HACK_LABEL;
	}


	return NOT_HACK_INSTRUCTION;
}

int run_regex(char* instruction, char* regex_string) {
	regex_t regex;
	int regex_result;

	regex_result = regcomp(&regex, regex_string, REG_EXTENDED);

	if (regex_result) {
		printf("Unable to compile regex\n");
	}

	regex_result = regexec(&regex, instruction, 0, NULL, 0);

	return regex_result;
}
