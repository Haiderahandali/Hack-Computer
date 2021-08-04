(SimpleFunction$SimpleFunction.test)
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
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
@SP
A = M - 1
M = !M
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
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
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
(END)
@END
0;JMP
