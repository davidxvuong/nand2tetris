#include "parser.h"

void reset_mem_address() {
	memory_address = 16;
}

char* translate_instruction(char* instruction) {
	char* result = NULL;

	int instruction_type = get_instruction_type(instruction);

	if (instruction_type == HACK_A_INSTRUCTION) {

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
		else {
			//Value found. Convert this value to binary
			result = convert_int_to_bin(value);
		}

		strcat(result, "\n");
	}
	else if (instruction_type == HACK_C_INSTRUCTION) {

		//Find if they have the delimiters = and ;. If they do, extract the text before it and find its corresponding binary values
		int index_of_equals = 0;
		int index_of_semi_colon = 0;
		int dest_len, comp_len, jump_len;
		char* ptr_to_equals = strchr(instruction, '=');
		char* ptr_to_semi_colon = strchr(instruction, ';');
		char* dest, *comp, *jump;
		char* dest_bits, *comp_bits, *jump_bits;

		if (ptr_to_equals != NULL && ptr_to_semi_colon != NULL) {
			//Instruction is in the form DEST=COMP;JMP

			index_of_equals = (int)(ptr_to_equals - instruction);
			index_of_semi_colon = (int)(ptr_to_semi_colon - instruction);

			dest_len = index_of_equals;
			comp_len = index_of_semi_colon - index_of_equals - 1;
			jump_len = 3;


			dest = (char*)(malloc(sizeof(char) * (dest_len + 1)));
			comp = (char*)(malloc(sizeof(char) * (comp_len + 1)));
			jump = (char*)(malloc(sizeof(char) * (jump_len + 1)));

			strncpy(dest, instruction, dest_len);
			dest[dest_len] = '\0';

			strncpy(comp, instruction + index_of_equals + 1, comp_len);
			comp[comp_len] = '\0';

			strncpy(jump, instruction + index_of_semi_colon + 1, jump_len);
			jump[jump_len] = '\0';
		}
		else if (ptr_to_equals == NULL && ptr_to_semi_colon  != NULL) {
			//Instruction is in the form COMP;JMP

			index_of_semi_colon = (int)(ptr_to_semi_colon - instruction);

			comp_len = index_of_semi_colon;
			jump_len = 3;

			dest = NULL;
			comp = (char*)(malloc(sizeof(char) * (comp_len + 1)));
			jump = (char*)(malloc(sizeof(char) * (jump_len + 1)));

			strncpy(comp, instruction + index_of_equals, comp_len);
			comp[comp_len] = '\0';

			strncpy(jump, instruction + index_of_semi_colon + 1, jump_len);
			jump[jump_len] = '\0';

		}
		else if (ptr_to_equals != NULL && ptr_to_semi_colon == NULL) {
			//Instruction is in the form DEST=COMP

			index_of_equals = (int)(ptr_to_equals - instruction);

			dest_len = index_of_equals;
			comp_len = (int)(strlen(instruction)) - index_of_equals;

			dest = (char*)(malloc(sizeof(char) * (dest_len + 1)));
			comp = (char*)(malloc(sizeof(char) * (comp_len + 1)));
			jump = NULL;

			strncpy(dest, instruction, dest_len);
			dest[dest_len] = '\0';

			strncpy(comp, instruction + index_of_equals + 1, comp_len);
			comp[comp_len] = '\0';

		}

		dest_bits = get_dest_bits(dest);
		comp_bits = get_comp_bits(comp);
		jump_bits = get_jump_bits(jump);

		// if(dest_bits == NULL || comp_bits == NULL || jump_bits == NULL) {
		// 	//Fail safe case
		// 	return NULL;
		// }

		if (dest_bits == NULL) {
			printf("dest bits failed\n");
			return NULL;
		}
		if (comp_bits == NULL) {
			printf("comp bits failed\n");
			return NULL;
		}
		if (jump_bits == NULL) {
			printf("jump_bits failed\n");
			return NULL;
		}

		result = (char*)(malloc(sizeof(char) * MACHINE_CODE_LENGTH + 1));
		result[0] = '\0';

		strcat(result, C_INSTR_LEAD_BITS);
		strcat(result, comp_bits);
		strcat(result, dest_bits);
		strcat(result, jump_bits);
		strcat(result, "\n");

	}

	//We can treat labels as NULL as well because we don't need to translate these

	return result;
}

void parse_labels(char* instruction, int instruction_num) {
	int regex_result = run_regex(instruction, REGEX_LABEL);
	static int count = 0;

	if (!regex_result) {
		//Found label. remove brackets and store data into symbol table
		char* pch = strtok(instruction, "()");

		if (pch != NULL) {
			insert(pch, instruction_num - count);
			count++;
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

char* get_comp_bits(char* comp) {
	if (comp == NULL) {
		return NULL;
	}

	//String compare with every comp strings
	if (!strcmp(comp, S_COMP_ZERO)) {
		return B_COMP_ZERO;
	}
	else if (!strcmp(comp, S_COMP_ONE)) {
		return B_COMP_ONE;
	}
	else if (!strcmp(comp, S_COMP_NEG_ONE)) {
		return B_COMP_NEG_ONE;
	}
	else if (!strcmp(comp, S_COMP_D)) {
		return B_COMP_D;
	}
	else if (!strcmp(comp, S_COMP_A)) {
		return B_COMP_A;
	}
	else if (!strcmp(comp, S_COMP_M)) {
		return B_COMP_M;
	}
	else if (!strcmp(comp, S_COMP_NOT_D)) {
		return B_COMP_NOT_D;
	}
	else if (!strcmp(comp, S_COMP_NOT_A)) {
		return B_COMP_NOT_A;
	}
	else if (!strcmp(comp, S_COMP_NOT_M)) {
		return B_COMP_NOT_M;
	}
	else if (!strcmp(comp, S_COMP_NEG_A)) {
		return B_COMP_NEG_A;
	}
	else if (!strcmp(comp, S_COMP_NEG_D)) {
		return B_COMP_NEG_D;
	}
	else if (!strcmp(comp, S_COMP_NEG_M)) {
		return B_COMP_NEG_M;
	}
	else if (!strcmp(comp, S_COMP_D_PLUS_ONE)) {
		return B_COMP_D_PLUS_ONE;
	}
	else if (!strcmp(comp, S_COMP_A_PLUS_ONE)) {
		return B_COMP_A_PLUS_ONE;
	}
	else if (!strcmp(comp, S_COMP_M_PLUS_ONE)) {
		return B_COMP_M_PLUS_ONE;
	}
	else if (!strcmp(comp, S_COMP_D_MINUS_ONE)) {
		return B_COMP_D_MINUS_ONE;
	}
	else if (!strcmp(comp, S_COMP_A_MINUS_ONE)) {
		return B_COMP_A_MINUS_ONE;
	}
	else if (!strcmp(comp, S_COMP_M_MINUS_ONE)) {
		return B_COMP_M_MINUS_ONE;
	}
	else if (!strcmp(comp, S_COMP_D_PLUS_A)) {
		return B_COMP_D_PLUS_A;
	}
	else if (!strcmp(comp, S_COMP_D_PLUS_M)) {
		return B_COMP_D_PLUS_M;
	}
	else if (!strcmp(comp, S_COMP_D_MINUS_A)) {
		return B_COMP_D_MINUS_A;
	}
	else if (!strcmp(comp, S_COMP_D_MINUS_M)) {
		return B_COMP_D_MINUS_M;
	}
	else if (!strcmp(comp, S_COMP_A_MINUS_D)) {
		return B_COMP_A_MINUS_D;
	}
	else if (!strcmp(comp, S_COMP_M_MINUS_D)) {
		return B_COMP_M_MINUS_D;
	}
	else if (!strcmp(comp, S_COMP_D_AND_A)) {
		return B_COMP_D_AND_A;
	}
	else if (!strcmp(comp, S_COMP_D_AND_M)) {
		return B_COMP_D_AND_M;
	}
	else if (!strcmp(comp, S_COMP_D_OR_A)) {
		return B_COMP_D_OR_A;
	}
	else if (!strcmp(comp, S_COMP_D_OR_M)) {
		return B_COMP_D_OR_M;
	}
	else {
		//Fail safe case - I don't expect this case to be satisfied
		return NULL;
	}
}

char* get_dest_bits(char* dest) {
	if (dest == S_DEST_NULL) {
		return B_DEST_NULL;
	}
	else if (!strcmp(dest, S_DEST_M)) {
		return B_DEST_M;
	}
	else if (!strcmp(dest, S_DEST_D)) {
		return B_DEST_D;
	}
	else if (!strcmp(dest, S_DEST_MD)) {
		return B_DEST_MD;
	}
	else if (!strcmp(dest, S_DEST_A)) {
		return B_DEST_A;
	}
	else if (!strcmp(dest, S_DEST_AM)) {
		return B_DEST_AM;
	}
	else if (!strcmp(dest, S_DEST_AD)) {
		return B_DEST_AD;
	}
	else if (!strcmp(dest, S_DEST_AMD)) {
		return B_DEST_AMD;
	}
	else {
		//Fail safe case - I don't expect this case to be satisfied
		return NULL;
	}

}

char* get_jump_bits(char* jump) {
	if (jump == NULL) {
		return B_JUMP_NULL;
	}
	else if (!strcmp(jump, S_JUMP_JGT)) {
		return B_JUMP_JGT;
	}
	else if (!strcmp(jump, S_JUMP_JEQ)) {
		return B_JUMP_JEQ;
	}
	else if (!strcmp(jump, S_JUMP_JGE)) {
		return B_JUMP_JGE;
	}
	else if (!strcmp(jump, S_JUMP_JLT)) {
		return B_JUMP_JLT;
	}
	else if (!strcmp(jump, S_JUMP_JNE)) {
		return B_JUMP_JNE;
	}
	else if(!strcmp(jump, S_JUMP_JLE)) {
		return B_JUMP_JLE;
	}
	else if (!strcmp(jump, S_JUMP_JMP)) {
		return B_JUMP_JMP;
	}
	else {
		//Fail safe case - I don't expect this case to be satisfied
		return NULL;
	}
}
