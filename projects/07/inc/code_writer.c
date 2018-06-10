#include "code_writer.h"

char* generate_hack_instruction(vm_instr_t* instr, char* filename) {
	char* hack_instr = malloc(sizeof(char) * STRING_BUFFER);

	if (instr -> instr_type == ARITH_LOGIC_CMD) {
		//Arithmetic/logic command

		switch (instr -> logical_instr_info) {
			case ADD:
				strcpy(hack_instr, add_command());
				break;
			case SUB:
				strcpy(hack_instr, sub_command());
				break;
			case NEG:
				strcpy(hack_instr, neg_command());
				break;
			case EQ:
				strcpy(hack_instr, eq_command(jump_counter));
				jump_counter++;
				break;
			case GT:
				strcpy(hack_instr, gt_command(jump_counter));
				jump_counter++;
				break;
			case LT:
				strcpy(hack_instr, lt_command(jump_counter));
				jump_counter++;
				break;
			case AND:
				strcpy(hack_instr, and_command());
				break;
			case OR:
				strcpy(hack_instr, or_command());
				break;
			case NOT:
				strcpy(hack_instr, not_command());
				break;
		}
	}
	else {
		mem_instr_t* mem_info = instr -> mem_instr_info;
		int value = mem_info -> value;

		if (instr -> instr_type == POP_CMD) {
			//Pop command

			switch (mem_info -> mem_segment) {
				case LOCAL:
					strcpy(hack_instr, pop_local_command(value));
					break;
				case ARG:
					strcpy(hack_instr, pop_argument_command(value));
					break;
				case THIS:
					strcpy(hack_instr, pop_this_command(value));
					break;
				case THAT:
					strcpy(hack_instr, pop_that_command(value));
					break;
				case STATIC:
					strcpy(hack_instr, pop_static_command(value, filename));
					break;
				case TEMP:
					strcpy(hack_instr, pop_temp_command(value));
					break;
				case POINTER:
					strcpy(hack_instr, pop_pointer_command(value));
					break;
			}
		}
		else {
			//Push command

			switch (mem_info -> mem_segment) {
				case LOCAL:
					strcpy(hack_instr, push_local_command(value));
					break;
				case ARG:
					strcpy(hack_instr, push_argument_command(value));
					break;
				case THIS:
					strcpy(hack_instr, push_this_command(value));
					break;
				case THAT:
					strcpy(hack_instr, push_that_command(value));
					break;
				case STATIC:
					strcpy(hack_instr, push_static_command(value, filename));
					break;
				case CONSTANT:
					strcpy(hack_instr, push_const_command(value));
					break;
				case TEMP:
					strcpy(hack_instr, push_temp_command(value));
					break;
				case POINTER:
					strcpy(hack_instr, push_pointer_command(value));
					break;
			}
		}
	}

	return hack_instr;
}

void initialize_jump_counter() {
	jump_counter = 0;
}

//Helper functions
char* push_command(int val, char* segPtr) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@%s\nD=D+M\n@addr\nM=D\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", val, segPtr);

	return cmd;
}

char* pop_command(int val, char* segPtr) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@%s\nD=D+M\n@addr\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@addr\nA=M\nM=D\n", val, segPtr);

	return cmd;
}

char* cmp_branch_command(int counter, char* jump_type) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nD=M-D\n@B_%s_%d\nD;%s\n@SP\nA=M\nM=0\n@B_%s_END_%d\n0;JMP\n(B_%s_%d)\n@SP\nA=M\nM=-1\n(B_%s_END_%d)\n@SP\nM=M+1\n", jump_type, counter, jump_type, jump_type, counter, jump_type, counter, jump_type, counter);

	return cmd;
}

char* double_operand_command(char* operation) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=%s\n@SP\nM=M+1\n", operation);

	return cmd;
}

char* push_local_command(int val) {
	return push_command(val, "LCL");
}

char* pop_local_command(int val) {
	return pop_command(val, "LCL");
}

char* push_argument_command(int val) {
	return push_command(val, "ARG");
}

char* pop_argument_command(int val) {
	return pop_command(val, "ARG");
}

char* push_this_command(int val) {
	return push_command(val, "THIS");
}

char* pop_this_command(int val) {
	return pop_command(val, "THIS");
}

char* push_that_command(int val) {
	return push_command(val, "THAT");
}

char* pop_that_command(int val) {
	return pop_command(val, "THAT");
}

char* push_const_command(int val) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", val);

	return cmd;
}

char* push_static_command(int val, char* filename) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%s.%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", filename, val);

	return cmd;
}

char* pop_static_command(int val, char* filename) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@SP\nM=M-1\nA=M\nD=M\n@%s.%d\nM=D\n", filename, val);

	return cmd;
}

char* push_temp_command(int val) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@5\nD=D+A\n@addr\nM=D\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", val);

	return cmd;
}

char* pop_temp_command(int val) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@5\nD=D+A\n@addr\nM=D\n@SP\nM=M-1\n@SP\nA=M\nD=M\n@addr\nA=M\nM=D\n", val);

	return cmd;
}

char* push_pointer_command(int val) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@3\nD=D+A\n@addr\nM=D\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", val);

	return cmd;
}

char* pop_pointer_command(int val) {
	char* cmd = malloc(sizeof(char) * STRING_BUFFER);

	sprintf(cmd, "@%d\nD=A\n@3\nD=D+A\n@addr\nM=D\n@SP\nM=M-1\n@SP\nA=M\nD=M\n@addr\nA=M\nM=D\n", val);

	return cmd;
}

char* add_command() {
	return double_operand_command("M+D");
}

char* sub_command() {
	return double_operand_command("M-D");
}

char* neg_command() {
	return "@SP\nM=M-1\nA=M\nM=-M\n@SP\nM=M+1\n";
}

char* eq_command(int counter) {
	return cmp_branch_command(counter, "JEQ");
}

char* gt_command(int counter) {
	return cmp_branch_command(counter, "JGT");
}

char* lt_command(int counter) {
	return cmp_branch_command(counter, "JLT");
}

char* and_command() {
	return double_operand_command("D&M");
}

char* or_command() {
	return double_operand_command("D|M");
}

char* not_command() {
	return "@SP\nM=M-1\nA=M\nM=!M\n@SP\nM=M+1\n";
}