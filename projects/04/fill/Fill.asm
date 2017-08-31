// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

//Base address for Screen: 16384
//Address for Keyboard: 24576

(LOOP)
	@SCREEN
	D=A

	@i
	M=D

	@KBD
	D=M

	@WHITE
	D; JEQ		//branch if nothing is pressed 


//set screen to black
(BLACK)
	@i
	A=M
	M=-1

	@i
	M=M+1

	@KBD
	D=A

	@i
	D=M-D

	@BLACK
	D; JNE

	@SKIP
	0; JEQ

(WHITE)
	@i
	A=M
	M=0

	@i
	M=M+1

	@KBD
	D=A

	@i
	D=M-D

	@WHITE
	D; JNE

(SKIP)

	@LOOP
	0; JEQ