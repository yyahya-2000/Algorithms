There are N stones with different weights P. It is necessary to find a set of stones with a maximum total weight not exceeding W.
It is necessary to solve the problem using dynamic programming.
Input format
There are 3 lines in the input file:

In the first line, the number N is the number of available stones.
1 <= N <= 1000

In the second line, the number W is the maximum weight limit.
0 <= W <= 50000

The third line contains N numbers, these are the weights of the available stones.
Let the weight of the stone be P, then 1 <= P <= 8000
The set is ordered in ascending order of weight, but stones of the same weight can be found!

Output format
You need to write 3 lines to the output file:

In the first line, the number A is the total weight of all stones included in the solution.
Estimated Limitations: 0 <= A <= 50,000

In the second line, the number M is the number of stones included in the solution.
Estimated Limitations: 0 <= M <= 1000

The third line contains M numbers, these are the weights of the stones taken.
Let the weight of the stone be P, then 1 <= P <= 8000
All weights must be from the input data and must be in non-decreasing order.