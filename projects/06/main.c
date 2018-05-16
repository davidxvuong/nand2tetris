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

void insert_list(char* instruction) {
	node_t* node = (node_t*)(malloc(sizeof(char)));
	node_t* ptr;

	node -> instruction = instruction;

	if (list -> head == NULL) {
		list -> head = node;
	}
	else {
		ptr = list -> head;

		while (ptr -> next != NULL) {
			ptr = ptr -> next;
		}

		ptr -> next = node;
	}

	++(list -> length);
}

void print_list() {
	node_t* ptr = list -> head;

	while (ptr != NULL) {
		printf("%s", ptr -> instruction);
		ptr = ptr -> next;
	}
}

int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("Invalid parameters\n");

		return -1;
	}

	//TODO: check for valid .asm file

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
			insert_list(buf);
			
		}
	}

	fclose(fp);

	print_list();

	kill_list();
	kill_table();

	return 0;
}