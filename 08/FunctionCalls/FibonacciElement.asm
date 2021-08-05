@Sys.init
0;JMP
//Generate Function Label Main.fibonacci
(Main.fibonacci)
@0
D = A
@SP
M = M + D
// Push Arg 0
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Constant 2
@2 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Less Than
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
D = M - D
@LESSTHAN0
D; JLT

@SP
A = M - 1
M = 0
@LTDONE0
0;JMP
(LESSTHAN0)
@SP 
A = M - 1
M = -1
(LTDONE0)
//Write If Goto IF_TRUE
@SP
M = M - 1
A = M
D = M
@IF_TRUE
D;JNE
//Write goto IF_FALSE
@IF_FALSE
0;JMP
(IF_TRUE)
// Push Arg 0
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Return Function
@LCL
D = M
@R15 
M = D
@5
D = A
@R15
A = M - D
D = M
@R14 
M = D  
//Pop Argument 0 
@0
D = A
@ARG 
D = M + D
@R13
M = D
@SP
M = M - 1
A = M
D = M 
@R13
A = M
M = D
@ARG 
D = M + 1
@SP
M = D
@1
D = A
@R15
A = M - D
D = M
@THAT 
M = D
@2
D = A
@R15
A = M - D
D = M
@THIS 
M = D
@3
D = A
@R15
A = M - D
D = M
@ARG 
M = D
@4
D = A
@R15
A = M - D
D = M
@LCL 
M = D
@R14
A = M
0;JMP
(IF_FALSE)
// Push Arg 0
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Constant 2
@2 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Sub
@SP 
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M - D
//Call function Main.fibonacci
@Main.fibonacci$ret.0
 // push @returnAddress
D = A
@SP 
M = M + 1
A = M - 1
M = D
@LCL 
// Push LCL
D = M
@SP 
M = M + 1
A = M - 1
M = D
@ARG 
// Push ARG
D = M
@SP 
M = M + 1
A = M - 1
M = D
@THIS 
// Push THIS
D = M
@SP 
M = M + 1
A = M - 1
M = D
@THAT 
// Push THAT
D = M
@SP 
M = M + 1
A = M - 1
M = D

// ARG = SP - 5 - nArgs
@5
D = A
@SP
D = M - D
@1
D = D - A 
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
//------calling the function label
@Main.fibonacci 
0;JMP
(Main.fibonacci$ret.0)
// Push Arg 0
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Constant 1
@1 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Sub
@SP 
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M - D
//Call function Main.fibonacci
@Main.fibonacci$ret.1
 // push @returnAddress
D = A
@SP 
M = M + 1
A = M - 1
M = D
@LCL 
// Push LCL
D = M
@SP 
M = M + 1
A = M - 1
M = D
@ARG 
// Push ARG
D = M
@SP 
M = M + 1
A = M - 1
M = D
@THIS 
// Push THIS
D = M
@SP 
M = M + 1
A = M - 1
M = D
@THAT 
// Push THAT
D = M
@SP 
M = M + 1
A = M - 1
M = D

// ARG = SP - 5 - nArgs
@5
D = A
@SP
D = M - D
@1
D = D - A 
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
//------calling the function label
@Main.fibonacci 
0;JMP
(Main.fibonacci$ret.1)
//Add
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
//Return Function
@LCL
D = M
@R15 
M = D
@5
D = A
@R15
A = M - D
D = M
@R14 
M = D  
//Pop Argument 0 
@0
D = A
@ARG 
D = M + D
@R13
M = D
@SP
M = M - 1
A = M
D = M 
@R13
A = M
M = D
@ARG 
D = M + 1
@SP
M = D
@1
D = A
@R15
A = M - D
D = M
@THAT 
M = D
@2
D = A
@R15
A = M - D
D = M
@THIS 
M = D
@3
D = A
@R15
A = M - D
D = M
@ARG 
M = D
@4
D = A
@R15
A = M - D
D = M
@LCL 
M = D
@R14
A = M
0;JMP
//Generate Function Label Sys.init
(Sys.init)
@0
D = A
@SP
M = M + D
//Push Constant 4
@4 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Call function Main.fibonacci
@Main.fibonacci$ret.2
 // push @returnAddress
D = A
@SP 
M = M + 1
A = M - 1
M = D
@LCL 
// Push LCL
D = M
@SP 
M = M + 1
A = M - 1
M = D
@ARG 
// Push ARG
D = M
@SP 
M = M + 1
A = M - 1
M = D
@THIS 
// Push THIS
D = M
@SP 
M = M + 1
A = M - 1
M = D
@THAT 
// Push THAT
D = M
@SP 
M = M + 1
A = M - 1
M = D

// ARG = SP - 5 - nArgs
@5
D = A
@SP
D = M - D
@1
D = D - A 
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
//------calling the function label
@Main.fibonacci 
0;JMP
(Main.fibonacci$ret.2)
(WHILE)
//Write goto WHILE
@WHILE
0;JMP
