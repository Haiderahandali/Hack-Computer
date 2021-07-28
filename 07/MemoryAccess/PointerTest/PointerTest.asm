@3030 
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
@3040 
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
@32 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@2
D = A
@THIS 
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
@46 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@6
D = A
@THAT 
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
@THIS
 D = M
 @SP 
 M = M + 1
 A = M - 1
 M = D
@THAT
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
@2 
D = A
@THIS 
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
M = M - D
@6 
D = A
@THAT 
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
(END)
@END
0;JMP
