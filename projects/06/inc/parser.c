#include "parser.h"

void reset_mem_address() {
	memory_address = 16;
}

char* translate_instruction(char* instruction) {
	char* result = NULL;

	int instruction_type = get_instruction_type(instruction);

	if (instruction_type == HACK_A_INSTRUCTION) {
		// printf("%s\n", instruction + 1);
		int value = lookup(instruction + 1);
		if (value == -1) {
			//Symbol not found. still could be a value loaded into the A-register or a variable symbol
			char* ptr_to_symbol = strchr(instruction, '@');
			int index = (int)(ptr_to_symbol - instruction) + 1;
			char num_characters = 0;


			if (isdigit(instruction[index])) {
				//This is a value. Get it's binary representation
				int value = atoi(ptr_to_symbol + 1);
				result = convert_int_to_bin(value);
			}
			else {
				//This is a variable. Store symbol into symbol table and get binary representation its memory address
				while(!isspace(instruction[index])) {
					index++;
					num_characters++;
				}
				char* value = (char*)(malloc(sizeof(char) * (num_characters + 1)));

				value[0] = '\0';

				strncpy(value, ptr_to_symbol + 1, num_characters);

				insert(value, memory_address);

				result = convert_int_to_bin(memory_address);

				memory_address++;
			}
		}
	}
	else if (instruction_type == HACK_C_INSTRUCTION) {
		// char* pch = strtok(instruction, "=;");
		// while (pch != NULL) {
		// 	printf("%s\n", pch);
		// 	pch = strtok(NULL, "=;");
		// }
	}

	return result;
}

void parse_labels(char* instruction, int instruction_num) {
	int regex_result = run_regex(instruction, REGEX_LABEL);

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

char* convert_int_to_bin(int value) {
	char* result = (char*)(malloc(sizeof(char) * MACHINE_CODE_LENGTH + 1));
	int quotient = value;
	int binary = 0;
	int count = 0;

	result[0] = '\0';

	while(quotient != 0) {
		binary = quotient % 2;
		quotient = quotient / 2;

		if (binary) {
			strcat(result, "1");
		}
		else {
			strcat(result, "0");
		}
		count++;
	}

	while (count < MACHINE_CODE_LENGTH) {
		strcat(result, "0");
		count++;
	}

	reverse_string(result, MACHINE_CODE_LENGTH);

	return result;
}

void reverse_string(char* str, int length) {
	int start = 0;
	int end = length - 1;
	char temp;


	while (start <= end) {
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

void remove_whitespaces(char* str) {
	int length = strlen(str);
	int count = 0;
	int i, j;

	if (length <= 1) {
		return;
	}

	for (i = 0; i < length; i++) {
		if (isspace(str[i])) {
			count++;
		}
		else if (count > 0) {
			for (j = i; j < length; j++) {
				str[j-count] = str[j];
				str[j] = ' ';
			}

			i = i - count -1;
			count = 0;
		}
	}

	if (count > 0) {
		str[length - count] = '\0';
	}

}