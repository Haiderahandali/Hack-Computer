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

//int Size = 256 * 512 = 8000 * 16

//Got the size of screen and store it at Size
@8000
D = A
@Size
M = D 

@Bcount
M = 0
@Wcount
M = 0

(START)
//--------------------- START -----------------------------//
//if keyboard is pressed, 
//start printing white pixels
@KBD
D = M
@PRINT_WHITE
D; JNE

//--------------------- Printing Black -----------------------------//
(PRINT_BLACK)
//Reset the Wcount to 0
@Wcount
M = 0

//if I am at the last pixel, do nothing
@Size
D = M
@Bcount
D = D - M
@START
D;JEQ

//put a black pixel to the screen, and increment the counter by one
@SCREEN
D = A
@Bcount 
A = M + D
//screen address + Bcount address is selected

M = 0

@Bcount
M = M + 1

@START
0;JMP


//--------------------- Printing White -----------------------------//
(PRINT_WHITE)

//if I am at the last pixel, do nothing
@Size
D = M
@Wcount
D = D - M
@START
D;JEQ

//Reset the Bcount to 0
@Bcount
M = 0

//put a black pixel to the screen, and increment the counter by one
@SCREEN
D = A
@Wcount 
A = M + D
//screen address + Bcount address is selected

M = -1

@Wcount
M = M + 1

@START
0;JMP
