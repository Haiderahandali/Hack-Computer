@Sys.init$ret.0
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
@0
D = D - A 
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
//------calling the function label
@Sys.init 
0;JMP
(Sys.init$ret.0)
(Main.fibonacci)
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@2 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
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
@SP
M = M - 1
A = M
D = M
@IF_TRUE
D;JNE
@IF_FALSE
0;JMP
(IF_TRUE)
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@0
D = A
@ARG 
D = M + D
@R15
M = D
@SP
M = M - 1
A = M
D = M 
@R15
A = M
M = D
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
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@2 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@SP 
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M - D
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
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@1 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@SP 
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M - D
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
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
@0
D = A
@ARG 
D = M + D
@R15
M = D
@SP
M = M - 1
A = M
D = M 
@R15
A = M
M = D
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
(Sys.init)
@4 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@Main.fibonacci$ret.3
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
(Main.fibonacci$ret.3)
(WHILE)
@WHILE
0;JMP
