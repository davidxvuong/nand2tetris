#include "symbol_table.h"

void initialize_table() {
	symbol_table = (table_t*)(malloc(sizeof(table_t)));
	symbol_table -> head = NULL;
	symbol_table -> size = 0;

	//TODO: add default symbols
	int i;

	for (i = 0; i < 16; i++) {
		char* buf = malloc(STRING_BUFFER*sizeof(char));
		sprintf(buf, "R%d", i);
		insert(buf, i);
	}

	insert("SCREEN", SCREEN);
	insert("KBD", KBD);
	insert("SP", SP);
	insert("LCL", LCL);
	insert("ARG", ARG);
	insert("THIS", THIS);
	insert("THAT", THAT);
}

void kill_table() {
	map_t* ptr;

	while (symbol_table -> head -> next != NULL) {
		ptr = symbol_table -> head;
		symbol_table -> head = symbol_table -> head -> next;

		free(ptr);
	}

	free(symbol_table);
}

void print_table() {
	map_t* ptr = symbol_table -> head;

	while(ptr != NULL) {
		printf("Key: %s Value: %d\n", ptr -> key, ptr -> value);
		ptr = ptr -> next;
	}
}

void insert(char* key, int value) {
	map_t* node = (map_t*)(malloc(sizeof(map_t)));
	node -> key = key;
	node -> value = value;
	node -> next = NULL;

	if (symbol_table -> head == NULL) {
		symbol_table -> head = node;
	}
	else {
		map_t* node_ptr = symbol_table -> head;

		while(node_ptr -> next != NULL) {
			node_ptr = node_ptr -> next;
		}

		node_ptr -> next = node;
	}

	++(symbol_table -> size);
}

int lookup(char* key) {
	map_t* ptr = symbol_table -> head;
	
	while (ptr != NULL) {
		if (strcmp(ptr -> key, key) == 0) {
			return (ptr -> value);
		}
		ptr = ptr -> next;
	}

	return -1;
}
