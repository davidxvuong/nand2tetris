#ifndef HACK_ISA_H
#define HACK_ISA_H

//C-instruction leading bits
#define C_INSTR_LEAD_BITS		"111"

//A-Instrcution leading bits
#define A_INSTR_LEAD_BITS		"0"

//Comp Strings
#define S_COMP_ZERO				"0"
#define S_COMP_ONE 				"1"
#define S_COMP_NEG_ONE			"-1"
#define S_COMP_D 				"D"
#define S_COMP_A 				"A"
#define S_COMP_M 				"M"
#define S_COMP_NOT_D			"!D"
#define S_COMP_NOT_A 			"!A"
#define S_COMP_NOT_M 			"!M"
#define S_COMP_NEG_D 			"-D"
#define S_COMP_NEG_A 			"-A"
#define S_COMP_NEG_M 			"-M"
#define S_COMP_D_PLUS_ONE		"D+1"
#define S_COMP_A_PLUS_ONE 		"A+1"
#define S_COMP_M_PLUS_ONE 		"M+1"
#define S_COMP_D_MINUS_ONE		"D-1"
#define S_COMP_A_MINUS_ONE		"A-1"
#define S_COMP_M_MINUS_ONE		"M-1"
#define S_COMP_D_PLUS_A			"D+A"
#define S_COMP_D_PLUS_M			"D+M"
#define S_COMP_D_MINUS_A		"D-A"
#define S_COMP_D_MINUS_M		"D-M"
#define S_COMP_A_MINUS_D		"A-D"
#define S_COMP_M_MINUS_D		"M-D"
#define S_COMP_D_AND_A			"D&A"
#define S_COMP_D_AND_M			"D&M"
#define S_COMP_D_OR_A			"D|A"
#define S_COMP_D_OR_M			"D|M"

//Comp bits
#define B_COMP_ZERO				"0101010"
#define B_COMP_ONE 				"0111111"
#define B_COMP_NEG_ONE			"0111010"
#define B_COMP_D 				"0001100"
#define B_COMP_A 				"0110000"
#define B_COMP_M 				"1110000"
#define B_COMP_NOT_D			"0001101"
#define B_COMP_NOT_A 			"0110001"
#define B_COMP_NOT_M 			"1110001"
#define B_COMP_NEG_D 			"0001111"
#define B_COMP_NEG_A 			"0110011"
#define B_COMP_NEG_M 			"1110011"
#define B_COMP_D_PLUS_ONE		"0011111"
#define B_COMP_A_PLUS_ONE 		"0110111"
#define B_COMP_M_PLUS_ONE 		"1110111"
#define B_COMP_D_MINUS_ONE		"0001010"
#define B_COMP_A_MINUS_ONE		"0110010"
#define B_COMP_M_MINUS_ONE		"1110010"
#define B_COMP_D_PLUS_A			"0000010"
#define B_COMP_D_PLUS_M			"1000010"
#define B_COMP_D_MINUS_A		"0010111"
#define B_COMP_D_MINUS_M		"1010011"
#define B_COMP_A_MINUS_D		"0000011"
#define B_COMP_M_MINUS_D		"1000011"
#define B_COMP_D_AND_A			"0000000"
#define B_COMP_D_AND_M			"1000000"
#define B_COMP_D_OR_A			"0010101"
#define B_COMP_D_OR_M			"1010101"

//Dest Strings
#define S_DEST_NULL				NULL
#define S_DEST_M				"M"
#define S_DEST_D				"D"
#define S_DEST_MD				"MD"
#define S_DEST_A				"A"
#define S_DEST_AM				"AM"
#define S_DEST_AD				"AD"
#define S_DEST_AMD				"AMD"

//Dest bits
#define B_DEST_NULL				"000"
#define B_DEST_M 				"001"
#define B_DEST_D 				"010"
#define B_DEST_MD 				"011"
#define B_DEST_A 				"100"
#define B_DEST_AM 				"101"
#define B_DEST_AD 				"110"
#define B_DEST_AMD 				"111"

//Jump Strings
#define S_JUMP_NULL				NULL
#define S_JUMP_JGT				"JGT"
#define S_JUMP_JEQ				"JEQ"
#define S_JUMP_JGE				"JGE"
#define S_JUMP_JLT				"JLT"
#define S_JUMP_JNE				"JNE"
#define S_JUMP_JLE				"JLE"
#define S_JUMP_JMP				"JMP"

//Jump bits
#define B_JUMP_NULL				"000"
#define B_JUMP_JGT				"001"
#define B_JUMP_JEQ				"010"
#define B_JUMP_JGE				"011"
#define B_JUMP_JLT				"100"
#define B_JUMP_JNE				"101"
#define B_JUMP_JLE				"110"
#define B_JUMP_JMP				"111"

#endif