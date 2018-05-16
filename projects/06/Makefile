all: hackassembler

clean:
	rm HackAssembler

hackassembler: main.c 
	gcc main.c inc/symbol_table.c inc/parser.c inc/hack_isa.h -g -o HackAssembler