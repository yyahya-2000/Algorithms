Each PI student does a lot of things at the same time (solving problems, completing coursework, playing Dota 2, etc.).
Scheduling your day can be tricky.
Moreover, the subtlety lies in the fact that, as a rule (SIC!), The student does not have time to do all the work.
You should develop a program to help you plan your day.

Each student codes all their affairs with integers from 1 to N.
A student can complete M tasks per day (0 <M ≤ N ≤ 1500).
Possible day distributions of tasks can be generated as all possible combinations of N elements by M in lexicographic order.
For example, for N = 4, M = 2, the following combinations are generated:
1 - 1 2 (1 and 2 tasks)
2 - 1 3 (1 and 3 tasks)
3 - 1 4
4 - 2 3
5 - 2 4
6 - 3 4
It is easy to see that for N = M the student has time to complete all the tasks.

As a result of its work, the program displays the k-th plan for the day, where.
This way the student can try different plans.

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
4
2

Output:
2 3
