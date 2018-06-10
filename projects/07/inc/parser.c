#include "parser.h"

pair_t* parser_table = NULL;

vm_instr_t* parse_instruction(char* instr) {
	char* ptr = strstr(instr, "//");

	if (ptr != NULL) {
		return NULL;
	}

	vm_instr_t* vm_instr_info = NULL;
	int regex_result;

	regex_result = run_regex(instr, MEM_CMD_REGEX);

	if (!regex_result) {
		//This is a memory stack command (push/pop)
		vm_instr_info = malloc(sizeof(vm_instr_t));

		regex_result = run_regex(instr, PUSH_CMD_REGEX);

		if (!regex_result) {
			//push cmd
			vm_instr_info -> instr_type = PUSH_CMD;
		}
		else {
			//pop cmd
			vm_instr_info -> instr_type = POP_CMD;
		}

		mem_instr_t* mem_info = malloc(sizeof(mem_instr_t));

		mem_info -> mem_segment = get_mem_segment(instr);
		mem_info -> value = get_mem_value(instr);

		vm_instr_info -> mem_instr_info = mem_info;

		return vm_instr_info;
	}

	regex_result = run_regex(instr, ARITH_LOGIC_CMD_REGEX);

	if (!regex_result) {
		//This is an arithmetic/logic command

		remove_whitespaces(instr);

		vm_instr_info = malloc(sizeof(vm_instr_t));
		vm_instr_info -> instr_type = ARITH_LOGIC_CMD;
		vm_instr_info -> logical_instr_info = find_parser_value(instr);
	
		return vm_instr_info;
	}

	//In case if we don't recognize any of the commands or if its invalid syntax, we return NULL
	return NULL;
}

int run_regex(char* str, char* regex_str) {
	regex_t regex;
	int result;

	result = regcomp(&regex, regex_str, REG_EXTENDED);

	if (result) {
		printf("Unable to compile regex expression\n");
		return -1;
	}

	result = regexec(&regex, str, 0, NULL, 0);

	return result;
}

int get_mem_segment(char* str) {
	char* first_ptr = strchr(str, ' ');
	char* last_ptr = strrchr(str, ' ');
	int length = (int)(last_ptr - first_ptr) - 1;
	int index = (int)(first_ptr - str) + 1;
	char segment[length + 1];

	strncpy(segment, &str[index], length);
	segment[length] = '\0';

	return find_parser_value(segment);
}

int get_mem_value(char* str) {
	char* last_ptr = strrchr(str, ' ');
	int index = (int)(last_ptr - str) + 1;
	int length = index;
	char segment [length + 1];
	int result;

	strcpy(segment, &str[index]);
	segment[length] = '\0';

	//Convert to integer
	result = strtol(segment, NULL, 10);

	return result;	
}

char* copy_string(char* str) {
	int length = strlen(str);
	char* val = malloc(sizeof(char) * (length + 1));

	strcpy(val, str);
	val[length] = '\0';

	return val;
}

void initialize_parser_hash_table() {
	//shove things into hash table

	add_parser_value(AL_ADD, ADD);
	add_parser_value(AL_SUB, SUB);
	add_parser_value(AL_NEG, NEG);
	add_parser_value(AL_EQ, EQ);
	add_parser_value(AL_GT, GT);
	add_parser_value(AL_LT, LT);
	add_parser_value(AL_AND, AND);
	add_parser_value(AL_OR, OR);
	add_parser_value(AL_NOT, NOT);

	add_parser_value(MEM_LOCAL, LOCAL);
	add_parser_value(MEM_ARG, ARG);
	add_parser_value(MEM_THIS, THIS);
	add_parser_value(MEM_THAT, THAT);
	add_parser_value(MEM_CONSTANT, CONSTANT);
	add_parser_value(MEM_STATIC, STATIC);
	add_parser_value(MEM_POINTER, POINTER);
	add_parser_value(MEM_TEMP, TEMP);
}

void kill_parser_hash_table() {
	pair_t* cur_ptr, * tmp;

	HASH_ITER(hh, parser_table, cur_ptr, tmp) {
		HASH_DEL(parser_table, cur_ptr);

		free(cur_ptr);
	}
}

void add_parser_value(char* id, int value) {
	//make a copy of id before using it
	char* local_id = copy_string(id);
	pair_t* s;

	HASH_FIND_STR(parser_table, local_id, s);

	if (s == NULL) {
		s = malloc(sizeof(pair_t));
		s -> id = local_id;
		s -> value = value;
		HASH_ADD_KEYPTR(hh, parser_table, s -> id, strlen(s -> id), s);
	}
}

int find_parser_value(char* id) {
	char* local_id = copy_string(id);

	pair_t* s;

	HASH_FIND_STR(parser_table, local_id, s);

	return s -> value;
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
