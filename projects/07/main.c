#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/parser.h"
#include "inc/code_writer.h"

#define ARGV_INDEX 1

#ifndef STRING_BUFFER
#define STRING_BUFFER 256
#endif

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

	result = malloc(sizeof(char) * (string_length - old_string_length + new_string_length + 1));

	strncpy(result, string, string_length - old_string_length);
	result[string_length - old_string_length] = '\0';
	strcat(result, new_string);

	return result;
}

//Gets the file name
char* get_file_name(const char* str) {
	char* result = NULL;
	char* start_ptr = strrchr(str, '/') + 1;
	char* last_ptr = strrchr(str, '.') - 1;
	int length = (int)(last_ptr - start_ptr) + 1;

	result = malloc(sizeof(char) * (length + 1));
	strncpy(result, start_ptr, length);
	result[length] = '\0';

	return result;
}

int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("Invalid parameters\n");
		return -1;
	}

	char* mod_file_ext = replace_substring(argv[ARGV_INDEX], "vm", "asm");
	char* filename = get_file_name(argv[ARGV_INDEX]);

	FILE* read_fp = NULL;
	FILE* write_fp = NULL;


	read_fp = fopen(argv[ARGV_INDEX], "r");
	write_fp =fopen(mod_file_ext, "w");

	if (read_fp == NULL) {
		printf("Unable to open read file\n");
		return -1;
	}

	if (write_fp == NULL) {
		printf("Unable to open write file\n");
		return -1;
	}

	initialize_parser_hash_table();
	initialize_jump_counter();

	while(!feof(read_fp)) {
		vm_instr_t* parsed_instr = NULL;
		char* buf = malloc(sizeof(char) * STRING_BUFFER);
		memset(buf, 0, sizeof(buf));
		
		fgets(buf, STRING_BUFFER, read_fp);
		// remove_whitespaces(buf);
		parsed_instr = parse_instruction(buf);

		if (parsed_instr != NULL) {
			char* asm_instr = generate_hack_instruction(parsed_instr, filename);
			char* comment_vm_instr = malloc(sizeof(char) * STRING_BUFFER);

			comment_vm_instr[0] = '\0';
			strcat(comment_vm_instr, "\n");
			strcat(comment_vm_instr, "//");
			strcat(comment_vm_instr, buf);

			if (strchr(buf, '\n') == NULL) {
				strcat(comment_vm_instr, "\n");
			}

			fputs(comment_vm_instr, write_fp);
			fputs(asm_instr, write_fp);
			free(parsed_instr);
			free(comment_vm_instr);
		}

		free(buf);
	}

	fclose(read_fp);
	read_fp = NULL;

	fclose(write_fp);
	write_fp = NULL;

	kill_parser_hash_table();


	return 0;
}