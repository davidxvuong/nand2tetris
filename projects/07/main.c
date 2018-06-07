#include <stdio.h>
#include <stdlib.h>
#include "inc/parser.h"

#define ARGV_INDEX 1

#define STRING_BUFFER 256

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

	while(!feof(fp)) {
		char* buf = (char*)(malloc(sizeof(char) * STRING_BUFFER));
		fgets(buf, STRING_BUFFER, fp);

		printf("%s", buf);
	}

	fclose(fp);
	fp = NULL;

	return 0;
}