@Sys.init
0;JMP
//Generate Function Label Sys.init
(Sys.init)
@0
D = A
@SP
M = M + D
//Push Constant 4000
@4000 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Pointer THIS
 @SP 
 M = M - 1
 A = M
 D = M
@THIS
 M = D
//Push Constant 5000
@5000 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Pointer THAT
 @SP 
 M = M - 1
 A = M
 D = M
@THAT
 M = D
//Call function Sys.main
@Sys.main$ret.0
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
@Sys.main 
0;JMP
(Sys.main$ret.0)
//Pop Temp 1
@SP
M = M - 1
A = M
D = M 
@R6
M = D
(LOOP)
//Write goto LOOP
@LOOP
0;JMP
//Generate Function Label Sys.main
(Sys.main)
//Push Constant 0
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 0 
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
//Push Constant 0
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 1 
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
//Push Constant 0
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 2 
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
//Push Constant 0
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 3 
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
//Push Constant 0
@0 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 4 
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
@5
D = A
@SP
M = M + D
//Push Constant 4001
@4001 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Pointer THIS
 @SP 
 M = M - 1
 A = M
 D = M
@THIS
 M = D
//Push Constant 5001
@5001 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Pointer THAT
 @SP 
 M = M - 1
 A = M
 D = M
@THAT
 M = D
//Push Constant 200
@200 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 1 
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
//Push Constant 40
@40 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 2 
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
//Push Constant 6
@6 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Local 3 
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
//Push Constant 123
@123 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Call function Sys.add12
@Sys.add12$ret.1
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
@Sys.add12 
0;JMP
(Sys.add12$ret.1)
//Pop Temp 0
@SP
M = M - 1
A = M
D = M 
@R5
M = D
//Push Local 0
@0 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Local 1
@1 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Local 2
@2 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Local 3
@3 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Push Local 4
@4 
D = A
@LCL 
A = M + D   
D = M 
@SP 
M = M + 1
A = M - 1
M = D
//Add
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
//Add
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
//Add
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
//Add
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
//Pop Argument 0 
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
//Generate Function Label Sys.add12
(Sys.add12)
@0
D = A
@SP
M = M + D
//Push Constant 4002
@4002 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Pointer THIS
 @SP 
 M = M - 1
 A = M
 D = M
@THIS
 M = D
//Push Constant 5002
@5002 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Pop Pointer THAT
 @SP 
 M = M - 1
 A = M
 D = M
@THAT
 M = D
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
//Push Constant 12
@12 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
//Add
@SP
A = M - 1
D = M
@SP
M = M - 1
A = M - 1
M = M + D
//Pop Argument 0 
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
