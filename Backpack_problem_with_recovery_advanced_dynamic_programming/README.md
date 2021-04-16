There is a backpack that can lift the maximum possible weight W. A set of items is also given, each item has two parameters - weight P and cost C. It is necessary to find a set of items of maximum value, the weight of a set of items is not more than W. It is necessary to solve the problem using dynamic programming.

All inputs and outputs are integer and non-negative. They are guaranteed to be of type int (4 bytes) without overflow.

Input format
There are 4 lines in the input file:

The first line contains an integer N - the number of items available. 1 <= N <= 1000

The second line contains an integer W - the maximum weight that the backpack can withstand. 0 <= W <= 50000

The third line contains N integers - the weights of the available items P. 1 <= P <= 2000 Items of the same weight can occur.

The fourth line contains N integers - the cost of available items C. 1 <= C <= 2000

There may be items of the same value. Attention (!) The set of items is not ordered in any way.

Output format
You need to write 5 lines to the output file:

In the first line, the number A is the total cost of all items included in the solution. Estimated limits: 0 <= A <= 2,000,000 (2 million, based on 1,000 items at 2,000 cost each).

In the second line, the number B is the total weight of all items included in the solution. Estimated Limitations: 0 <= B <= W

In the third line, the number M is the number of items included in the solution. Estimated Limitations: 0 <= M <= 1000

The fourth line contains M numbers - the weights of the items taken.

The fifth line contains M numbers - the cost of the items taken.

All combinations of weight and value must be from the input. You can return them in response in any order (but without breaking the weight-value combinations).
