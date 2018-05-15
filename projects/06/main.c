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