The number of female students of PI in the Z-th year - N (0 <N <1500).
All PI students must use eyeshadows of different shades. Thus, the number of colors is the same as the number of female students.
The distribution of shadows on each day is expressed by the line: 1 5 3 ... 2 N (there are exactly N integers from 1 to N in the line, the numbers are separated by spaces) - read as student 1 uses color 1, student 2 uses color 5, student 3 uses color 3, etc.
All possible variants of the distribution of shadows can be generated in lexicographic order.
For example, for N = 3, permutations are generated:
1 - 1 2 3
2 - 1 3 2
3 - 2 1 3
4 - 2 3 1
5 - 3 1 2
6 - 3 2 1
The program should, given the number of female students PI (N) and the number of the day k (0 <k ≤ N!), Return the distribution of the color of the shadows on that day.

Input format
The first line is an integer N
The second line is an integer k.

Output format
One line - the kth variant (in lexicographic order) of the arrangement of shadows, with a space as a separator.

Example:
Input:
3
6

Output:
3 2 1