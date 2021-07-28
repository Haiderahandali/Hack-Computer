@17 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@17 
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
D = D - M
@EQUAL0
D - M; JEQ
@SP
A = M - 1
M = 0
@EQDONE0
0;JMP
(EQUAL0)
@SP 
A = M - 1
M = -1
(EQDONE0)
@17 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@16 
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
D = D - M
@EQUAL1
D - M; JEQ
@SP
A = M - 1
M = 0
@EQDONE1
0;JMP
(EQUAL1)
@SP 
A = M - 1
M = -1
(EQDONE1)
@16 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@17 
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
D = D - M
@EQUAL2
D - M; JEQ
@SP
A = M - 1
M = 0
@EQDONE2
0;JMP
(EQUAL2)
@SP 
A = M - 1
M = -1
(EQDONE2)
@892 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@891 
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
D - M; JLT

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
@891 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@892 
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
@LESSTHAN1
D - M; JLT

@SP
A = M - 1
M = 0
@LTDONE1
0;JMP
(LESSTHAN1)
@SP 
A = M - 1
M = -1
(LTDONE1)
@891 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@891 
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
@LESSTHAN2
D - M; JLT

@SP
A = M - 1
M = 0
@LTDONE2
0;JMP
(LESSTHAN2)
@SP 
A = M - 1
M = -1
(LTDONE2)
@32767 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@32766 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@SP
A = M - 1
D = M;
@SP
M = M - 1
A = M - 1
D = M - D
@GREATERTHAN0
D - M; JGT

//less than
@SP
A = M - 1
M = 0
@GTDONE0
0;JMP
(GREATERTHAN0)
@SP 
A = M - 1
M = -1
(GTDONE0)
@32766 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@32767 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@SP
A = M - 1
D = M;
@SP
M = M - 1
A = M - 1
D = M - D
@GREATERTHAN1
D - M; JGT

//less than
@SP
A = M - 1
M = 0
@GTDONE1
0;JMP
(GREATERTHAN1)
@SP 
A = M - 1
M = -1
(GTDONE1)
@32766 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@32766 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@SP
A = M - 1
D = M;
@SP
M = M - 1
A = M - 1
D = M - D
@GREATERTHAN2
D - M; JGT

//less than
@SP
A = M - 1
M = 0
@GTDONE2
0;JMP
(GREATERTHAN2)
@SP 
A = M - 1
M = -1
(GTDONE2)
@57 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@31 
D = A 
@SP 
A = M 
M = D 
@SP
M = M + 1
@53 
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
@112 
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
@SP
A = M -1 
M = -M
@SP
A = M - 1
D = M
@SP 
M = M - 1
A = M - 1
M = D & M
@82 
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
M = D | M
@SP
A = M - 1
M = !M
(END)
@END
0;JMP
