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
(LOOP_START)
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
@LOOP_START
D;JNE
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
@THAT
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
@1 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@1
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
(MAIN_LOOP_START)
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
@COMPUTE_ELEMENT
D;JNE
@END_PROGRAM
0;JMP
(COMPUTE_ELEMENT)
@0 
D = A
@THAT 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@1 
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
@2
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
@THAT
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
M = M + D
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
@MAIN_LOOP_START
0;JMP
(END_PROGRAM)
@111 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@333 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@888 
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
@StaticTest.vm.8 
M = D
@SP 
M = M - 1
A = M
D = M
@StaticTest.vm.3 
M = D
@SP 
M = M - 1
A = M
D = M
@StaticTest.vm.1 
M = D
@StaticTest.vm.3
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@StaticTest.vm.1
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
@StaticTest.vm.8
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
