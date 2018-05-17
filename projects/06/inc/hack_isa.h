#ifndef HACK_ISA_H
#define HACK_ISA_H

//C-instruction leading bits
#define C_INSTR_LEAD_BITS	"111"

//A-Instrcution leading bits
#define A_INSTR_LEAD_BITS	"0"

//Comp bits
#define COMP_ZERO			"0101010"
#define COMP_ONE 			"0111111"
#define COMP_NEG_ONE 		"0111010"
#define COMP_D 				"0001100"
#define COMP_A 				"0110000"
#define COMP_M 				"1110000"
#define COMP_NOT_D 			"0001101"
#define COMP_NOT_A 			"0110001"
#define COMP_NOT_M			"0001111"
#define COMP_NEG_A			"0110011"
#define COMP_NEG_M			"1110011"
#define COMP_D_PLUS_ONE		"0011111"
#define COMP_A_PLUS_ONE		"0110111"
#define COMP_M_PLUS_ONE		"1110111"
#define COMP_D_MINUS_ONE	"0001010"
#define COMP_A_MINUS_ONE	"0110010"
#define COMP_M_MINUS_ONE	"1110010"
#define COMP_D_PLUS_A		"0000010"
#define COMP_D_PLUS_M		"1000010"
#define COMP_D_MINUS_A		"0010111"
#define COMP_D_MINUS_M		"1010111"
#define COMP_A_MINUS_D		"0000011"
#define COMP_M_MINUS_D		"1000011"
#define COMP_D_AND_A		"0000000"
#define COMP_D_AND_M		"1000000"
#define COMP_D_OR_A			"0010101"
#define COMP_D_OR_M			"1010101"

//Dest bits
#define DEST_NULL			"000"
#define DEST_M 				"001"
#define DEST_D 				"010"
#define DEST_MD 			"011"
#define DEST_A 				"100"
#define DEST_AM 			"101"
#define DEST_AD 			"110"
#define DEST_AMD 			"111"

//Jump bits
#define JUMP_NULL			"000"
#define JUMP_JGT			"001"
#define JUMP_JEQ			"010"
#define JUMP_JGE			"011"
#define JUMP_JLT			"100"
#define JUMP_JNE			"101"
#define JUMP_JLE			"110"
#define JUMP_JMP			"111"

#endif