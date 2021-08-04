(Sys$Sys.init)
@4000 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
 @SP 
 M = M - 1
 A = M
 D = M
@THIS
 M = D
@5000 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
 @SP 
 M = M - 1
 A = M
 D = M
@THAT
 M = D
@Sys$Sys.main.ret
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
@Sys$Sys.main
 
0;JMP
(Sys$Sys.main.ret
)
@SP
M = M - 1
A = M
D = M 
@R6
M = D
(FunctionCalls/NestedCall/Sys$LOOP)
@LOOP
0;JMP
(Sys$Sys.main)
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@0
D = A
@LCL 
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
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@1
D = A
@LCL 
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
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@2
D = A
@LCL 
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
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@3
D = A
@LCL 
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
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@4
D = A
@LCL 
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
@4001 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
 @SP 
 M = M - 1
 A = M
 D = M
@THIS
 M = D
@5001 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
 @SP 
 M = M - 1
 A = M
 D = M
@THAT
 M = D
@200 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@1
D = A
@LCL 
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
@40 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@2
D = A
@LCL 
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
@6 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@3
D = A
@LCL 
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
@123 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@Sys$Sys.add12.ret
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
@Sys$Sys.add12
 
0;JMP
(Sys$Sys.add12.ret
)
@SP
M = M - 1
A = M
D = M 
@R5
M = D
@0 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@1 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@2 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@3 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@4 
D = A
@LCL 
A = M + D   
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
M = M + D
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
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
(Sys$Sys.add12)
@4002 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
 @SP 
 M = M - 1
 A = M
 D = M
@THIS
 M = D
@5002 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
 @SP 
 M = M - 1
 A = M
 D = M
@THAT
 M = D
@0 
D = A
@ARG 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@12 
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
(END)
@END
0;JMP
