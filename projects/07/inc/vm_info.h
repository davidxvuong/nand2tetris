#ifndef VM_INFO
#define VM_INFO

#define MEM_CMD_REGEX "(push|pop)\\s(\\w)*\\s[[:digit:]]+"
#define ARITH_LOGIC_CMD_REGEX "(add|sub|neg|eq|gt|lt|and|or|not){1}"
#define COMMENT_REGEX "(//).*"
#define PUSH_CMD_REGEX "push\\s\\w+\\s[[:digit:]]+"
#define POP_CMD_REGEX "pop\\s\\w+\\s[[:digit:]]+"

enum cmd_type_enum {POP_CMD, PUSH_CMD, ARITH_LOGIC_CMD};
enum mem_seg_enum {LOCAL, ARG, THIS, THAT, CONSTANT, STATIC, POINTER, TEMP};
enum logical_enum {ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT};

#define AL_ADD 			"add"
#define AL_SUB 			"sub"
#define AL_NEG 			"neg"
#define AL_EQ 			"eq"
#define AL_GT 			"gt"
#define AL_LT 			"lt"
#define AL_AND 			"and"
#define AL_OR 			"or"
#define AL_NOT 			"not"

#define MEM_LOCAL 		"local"
#define MEM_ARG 		"argument"
#define MEM_THIS 		"this"
#define MEM_THAT 		"that"
#define MEM_CONSTANT 	"constant"
#define MEM_STATIC 		"static"
#define MEM_POINTER 	"point"
#define MEM_TEMP 		"temp"

//Helper macros

#define push_command(val, segPtr) "@"#val"\nD=A\n@"segPtr"\nD=D+M\n@addr\nM=D\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
#define pop_command(val, segPtr) "@"#val"\nD=A\n@"segPtr"\nD=D+M\n@addr\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@addr\nA=M\nM=D\n"
#define cmp_branch_command(counter, jmp_type) "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nD=D-M\n@B_"jmp_type"_"#counter"\nD;"jmp_type"\n@SP\nA=M\nM=0\n@B_"jmp_type"_END_"#counter"\nO;JMP\n(B_"jmp_type"_"counter")\n@SP\nA=M\nM=-1\n(B_"jmp_type"_END_"#counter")\n@SP\nM=M+1\n"
#define double_operand_command(operand) "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D"operand"M\n@SP\nM=M+1\n"

//command macros

//Memory commands
#define push_local_command(val) push_command(val, "LCL")
#define pop_local_command(val) pop_command(val, "LCL")
#define push_argument_command(val) push_command(val, "ARG")
#define pop_argument_command(val) pop_command(val, "ARG")
#define push_this_command(val) push_command(val, "THIS")
#define pop_this_command(val) pop_command(val, "THIS")
#define push_that_command(val) push_command(val, "THAT")
#define pop_that_command(val) pop_command(val, "THAT")
#define push_const_command(val) "@"#val"\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
#define pop_static_command(val, filename) "@SP\nM=M-1\nA=M\nD=M\n@"filename"."#val"M=D\n"
#define push_temp_command(val) "@"#val"\nD=A\n@5\nD=D+A\n@addr\nM=D\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
#define pop_temp_command(val) "@"#val"\nD=A\n@5\nD=D+A\n@addr\nM=D\n@SP\nM=M-1\n@SP\nA=M\nD=M\n@addr\nA=M\nM=D\n"
#define push_pointer_command(val) "@"#val"\nD=A\n@3\nD=D+A\n@addr\nM=D\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
#define pop_pointer_command(val) "@"#val"\nD=A\n@3\nD=D+A\n@addr\nM=D\n@SP\nM=M-1\n@SP\nA=M\nD=M\n@addr\nA=M\nM=D\n"

//Arithmetic/Logic Commands
#define add_command double_operand_command("+")
#define sub_command double_operand_command("-")
#define neg_command "@SP\nM-M-1\nA=M\nM=-M\n@SP\nM=M+1\n"
#define eq_command(counter) cmp_branch_command(counter, "JEQ")
#define gt_command(counter) cmp_branch_command(counter, "JGT")
#define lt_command(counter) cmp_branch_command(counter, "JLT")
#define and_command double_operand_command("&")
#define or_command double_operand_command("|")
#define not_command "@SP\nM=M-1\nA=M\nM=!M\n@SP\nM=M+1\n"

#endif