#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/symbol_table.h"

#ifndef ARGV_INDEX
#define ARGV_INDEX 1
#endif

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

int main(int argc, char* argv[]) {
	initialize_table();
	print_table();

	char tmp[STRING_BUFFER];
	int i;

	for (i = 0; i < 16; i++) {
		sprintf(tmp, "R%d", i);
		printf("%d\n", lookup(tmp));
	}

	printf("%d\n", lookup("SCREEN"));
	printf("%d\n", lookup("KBD"));
	printf("%d\n", lookup("SP"));
	printf("%d\n", lookup("LCL"));
	printf("%d\n", lookup("ARG"));
	printf("%d\n", lookup("THIS"));
	printf("%d\n", lookup("THAT"));

	kill_table();

	return 0;

	if (argc > 2) {
		printf("Invalid parameters\n");

		return -1;
	}

	//TODO: check for valid .asm file

	FILE* fp = NULL;
	char buffer[STRING_BUFFER];

	fp = fopen(argv[ARGV_INDEX], "r");

	if (fp == NULL) {
		printf("Unable to open file\n");

		return -1;
	}

	while(fgets(buffer, sizeof(buffer), fp)) {
		printf("%s\n", buffer);
		//TODO: parse code
	}

	fclose(fp);

	return 0;
}