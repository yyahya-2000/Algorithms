The student (ka) -model (s) has set himself the goal of choosing a new sweater every day.
In total, the student (s) have N sweaters (the student (s) designates them with codes 1,2, ..., N).
The student (s) chooses sweaters for M days (0 <M <N <1500).
The plan for M days for sweaters can be represented as all possible placements of M out of N objects in lexicographic order. For example, with N = 4, M = 2, placements are generated:
1 - 1 2 (on the first day choose sweater 1, and on the second - 2)
2 - 1 3
3 - 1 4
4 - 2 1
5 - 2 3
6 - 2 4
7 - 3 1
8 - 3 2
9 - 3 4
10 - 4 1
11 - 4 2
12 - 4 3
The program should produce the kth plan as a result, where.

Input format
Three lines, each containing one integer:
N
k
M

Output format
One line - k-th plan, use space as separator

Example:
Input:
4
5
2

Output:
2 3
