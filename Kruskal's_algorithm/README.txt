Input format
The input of the program is information about a connected undirected weighted graph in the following format:

The first line contains two integers N and M, where N is the number of vertices and M is the number of edges in the graph. All N vertices are numbered, numbered from 0 to N-1. The next M lines contain 3 numbers: A B W, where A and B are the numbers of the vertices that the edge connects, and W is the cost (weight) of the edge.

Restrictions: 2 <= N <= 1500, 1 <= M <= 30,000, 1 <= W <= 30,000. It is guaranteed that the initial graph is connected, that is, it is possible to get from any vertex to any one along the available edges. All edge weights are different, the same vertices are connected by no more than 1 edge. See example below.

Output format
The program outputs the minimum spanning tree in the following format:

The first line contains one integer K - the number of edges included in the solution, it is assumed K = N-1.

The next K lines should contain 3 numbers each, this is a description of the edges included in the solution, represented as 3 integers: A B W. Where A and B are the numbers of the vertices that the edge connects, and W is the cost (weight) of the edge.

The ribs must be from the original set given in the assignment. The description of the edge must strictly correspond to the description from the assignment. The edges must be ordered in ascending order of weight (Sorting has already been added in the template when writing the solution to the file). It is guaranteed that in the input data all weights are different, so the solution must include edges with different weights.

See example below.

Example:
Input:
7 11
0 1 3
0 3 2
0 6 9
1 3 10
1 4 6
1 5 8
1 6 1
2 3 4
2 6 7
4 5 11
4 6 5

Output:
6
1 6 1
0 3 2
0 1 3
2 3 4
4 6 5
1 5 8
