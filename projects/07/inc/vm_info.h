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
#define MEM_POINTER 	"pointer"
#define MEM_TEMP 		"temp"

#endif