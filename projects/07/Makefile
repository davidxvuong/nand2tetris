all: VMTranslator

clean:
	rm VMTranslator

VMTranslator: main.c 
	gcc main.c inc/parser.c inc/code_writer.c inc/hack_isa.h inc/vm_info.h -g -o VMTranslator