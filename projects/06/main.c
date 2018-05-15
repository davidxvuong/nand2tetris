#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define ARGV_INDEX 1
#define STRING_BUFFER 256
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
	}

	fclose(fp);

	return 0;
}