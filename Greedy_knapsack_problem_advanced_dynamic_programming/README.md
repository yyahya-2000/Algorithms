The Greedy Backpack Problem. It must be solved using a greedy algorithm. It does not solve the problem optimally (!).

The maximum possible lifting weight of the backpack is set W. It is necessary to find a set of maximum cost, the total weight of which is not more than W.
All inputs and outputs are integer and non-negative. They are guaranteed to be of type int (4 bytes) without overflow.

There is no special checker, so only one correct answer is suitable for this problem. We need an implementation of the greedy algorithm. Ambiguous situations may arise, we are guided by this rule. If both items have the same unit cost, then we take the one that weighs more (if it fits in the backpack, respectively). Example: N = 2, W = 10, objects: P1 = 7, C1 = 70, P2 = 5, C2 = 50, then the correct answer: we take the object P1 = 7, C1 = 70, since it weighs more and is included in backpack.

Input format
There are 4 lines in the input file:

In the first line, the number N is the number of items available. 1 <= N <= 1000

In the second line, the number W is the limit on the maximum weight of the backpack. 0 <= W <= 50000

The third line contains N numbers - the weights of the available items P. 1 <= P <= 2000 Items of the same weight may occur.

The fourth line contains N numbers - available items C. 1 <= С <= 2000 Items of the same value can be found.

Attention (!) The set of items is not ordered in any way. But in your decision to arrange it the way you need it.

Output format
You need to write 5 lines to the output file:

In the first line, the number A is the total value of all items included in the solution. Estimated limits: 0 <= A <= 2,000,000 (2 million, based on 1,000 items at 2,000 cost each).

In the second line, the number B is the total weight of all items included in the solution. Estimated Limitations: 0 <= B <= W

In the third line, the number M is the number of items included in the solution. Estimated Limitations: 0 <= M <= N

The fourth line contains M numbers, these are the weights of the items taken.

The fifth line contains M numbers, these are the costs of the items taken.

All combination and cost weights must be from the input. You can display them in any order (but without breaking the response weight-value combinations).
