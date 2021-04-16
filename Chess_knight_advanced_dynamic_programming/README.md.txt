Given a field of NxM cells, the knight is in the upper left cell (0,0). He can walk with the letter G (like in chess) but only down and to the right, that is, there are only 4 variants of movement (picture in LMS).

It is necessary to calculate how many different ways to get to the cell (N-1, M-1), if the numbering of rows and columns starts from zero.

Dynamic programming solution, lazy recursion.

Input format
Input data: two integers

N - the number of lines of the board, restrictions 1 <= N <= 50

M - number of board columns, constraints 1 <= M <= 30

The board may not be square, that is, examples are possible when N! = M.

Output format
Output data: one number

S - the number of ways to get the knight from the cell (0,0) to the cell (N-1, M-1).

Restrictions: 0 <= S <= 10 ** 16

Pay attention to the limitations, number will cause an overflow of int type, so it is suggested to use long long.