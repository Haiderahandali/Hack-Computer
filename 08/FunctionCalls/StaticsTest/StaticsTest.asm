@261
D = A
@SP
M = D
@Sys.init
0;JMP
(Class1.set)
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@SP 
M = M - 1
A = M
D = M
@Class1.0 
M = D
@1 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@SP 
M = M - 1
A = M
D = M
@Class1.1 
M = D
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
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
(Class1.get)
@Class1.0
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@Class1.1
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@SP 
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M - D
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
@6 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@8 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@Class1.set$ret.0
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
@2
D = D - A 
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
//------calling the function label
@Class1.set 
0;JMP
(Class1.set$ret.0)
@SP
M = M - 1
A = M
D = M 
@R5
M = D
@23 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@15 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@Class2.set$ret.1
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
@2
D = D - A 
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
//------calling the function label
@Class2.set 
0;JMP
(Class2.set$ret.1)
@SP
M = M - 1
A = M
D = M 
@R5
M = D
@Class1.get$ret.2
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
@Class1.get 
0;JMP
(Class1.get$ret.2)
@Class2.get$ret.3
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
@Class2.get 
0;JMP
(Class2.get$ret.3)
(WHILE)
@WHILE
0;JMP
(Class2.set)
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@SP 
M = M - 1
A = M
D = M
@Class2.0 
M = D
@1 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@SP 
M = M - 1
A = M
D = M
@Class2.1 
M = D
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
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
(Class2.get)
@Class2.0
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@Class2.1
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@SP 
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M - D
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