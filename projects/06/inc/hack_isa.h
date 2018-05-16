#ifndef HACK_ISA_H
#define HACK_ISA_H

//C-instruction leading bits
#define C_INSTR_LEAD_BITS	7

//A-Instrcution leading bits
#define A_INSTR_LEAD_BITS	0

//Comp bits
#define COMP_ZERO			42 				//0101010
#define COMP_ONE 			63				//0111111
#define COMP_NEG_ONE 		58				//0111010
#define COMP_D 				12 				//0001100
#define COMP_A 				48				//0110000
#define COMP_M 				112				//1110000
#define COMP_NOT_D 			13				//0001101
#define COMP_NOT_A 			49				//0110001
#define COMP_NOT_M			113				//1110001
#define COMP_NEG_D			15				//0001111
#define COMP_NEG_A			51				//0110011
#define COMP_NEG_M			115				//1110011
#define COMP_D_PLUS_ONE		31				//0011111
#define COMP_A_PLUS_ONE		55				//0110111
#define COMP_M_PLUS_ONE		119				//1110111
#define COMP_D_MINUS_ONE	10				//0001010
#define COMP_A_MINUS_ONE	50				//0110010
#define COMP_M_MINUS_ONE	114				//1110010
#define COMP_D_PLUS_A		2				//0000010
#define COMP_D_PLUS_M		66				//1000010
#define COMP_D_MINUS_A		23				//0010111
#define COMP_D_MINUS_M		87				//1010111
#define COMP_A_MINUS_D		3				//0000011
#define COMP_M_MINUS_D		67				//1000011
#define COMP_D_AND_A		0				//0000000
#define COMP_D_AND_M		64				//1000000
#define COMP_D_OR_A			21				//0010101
#define COMP_D_OR_M			85				//1010101

//Dest bits
#define DEST_NULL			0				//000
#define DEST_M 				1				//001
#define DEST_D 				2				//010
#define DEST_MD 			3				//011
#define DEST_A 				4				//100
#define DEST_AM 			5				//101
#define DEST_AD 			6				//110
#define DEST_AMD 			7				//111

//Jump bits
#define JUMP_NULL			0				//000
#define JUMP_JGT			1				//001
#define JUMP_JEQ			2				//010
#define JUMP_JGE			3				//011
#define JUMP_JLT			4				//100
#define JUMP_JNE			5				//101
#define JUMP_JLE			6				//110
#define JUMP_JMP			7				//111

#endif