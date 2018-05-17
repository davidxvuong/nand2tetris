#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/symbol_table.h"
#include "inc/parser.h"

#ifndef ARGV_INDEX
#define ARGV_INDEX 1
#endif

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

typedef struct node {
	char* instruction;
	int line_num;
	struct node* next;
} node_t;

typedef struct {
	int length;
	node_t* head;
} instruction_list_t;

instruction_list_t* list;

void initialize_list() {
	list = (instruction_list_t*)(malloc(sizeof(instruction_list_t)));
}

void kill_list() {
	node_t* ptr;

	while(list -> head != NULL) {
		ptr = list -> head;

		list -> head = list -> head -> next;

		free(ptr);
	}

	free(list);
}

int insert_list(char* instruction) {
	node_t* node = (node_t*)(malloc(sizeof(char)));
	node_t* ptr;
	int line_num;

	char* copy_instr = (char*)(malloc(sizeof(char) * STRING_BUFFER));
	memcpy(copy_instr, instruction, sizeof(char) * STRING_BUFFER);

	node -> instruction = copy_instr;

	if (list -> head == NULL) {
		list -> head = node;
		node -> line_num = 1;
	}
	else {
		ptr = list -> head;
		line_num = (list -> head -> line_num) + 1;

		while (ptr -> next != NULL) {
			ptr = ptr -> next;
			line_num++;
		}
		
		node -> line_num = line_num;
		ptr -> next = node;
	}

	++(list -> length);

	return (node -> line_num);
}

void print_list() {
	node_t* ptr = list -> head;

	while (ptr != NULL) {
		printf("%s", ptr -> instruction);
		ptr = ptr -> next;
	}
}

//Replace the first occurrance of the substring
char* replace_substring(const char* string, const char* old_string, const char* new_string) {
	char* result = NULL;
	int old_string_length = strlen(old_string);
	int new_string_length = strlen(new_string);
	int string_length = strlen(string);
	char* ptr = strstr(string, old_string);

	if (ptr == NULL) {
		return NULL;
	}

	result = (char*)(malloc(sizeof(char) * (string_length - old_string_length + new_string_length)));

	strncpy(result, string, string_length - old_string_length);
	result[string_length - old_string_length] = '\0';
	strcat(result, new_string);

	return result;
}

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

	//Initialize
	initialize_list();
	initialize_table();

	//Reading .asm and storing it away. Perform 1st pass to search for labels
	while(!feof(fp)) {
		// printf("%s\n", buffer);
		char* buf = (char*)(malloc(sizeof(char) * STRING_BUFFER));
		fgets(buf, STRING_BUFFER, fp);

		if (is_instruction(buf)) {
			remove_comments(buf);
			int line_num = insert_list(buf);
			parse_labels(buf, line_num);
		}
	}

	fclose(fp);

	fp = NULL;

	char* hack_file_name = replace_substring(argv[ARGV_INDEX], "asm", "hack");

	fp = fopen(hack_file_name, "w");

	//Perform 2nd pass and translate program into HACK machine code
	node_t* node = list -> head;

	while (node != NULL) {
		// printf("%s", node -> instruction);

		translate_instruction(node -> instruction);
		node = node -> next;
	}

	fclose(fp);

	// print_table();

	kill_list();
	kill_table();

	return 0;
}