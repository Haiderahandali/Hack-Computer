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
@Foo.8 
M = D
@SP 
M = M - 1
A = M
D = M
@Foo.3 
M = D
@SP 
M = M - 1
A = M
D = M
@Foo.1 
M = D
@Foo.3
D = M 
@SP 
M = M + 1
A = M - 1
M = D
@Foo.1
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
@Foo.8
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
