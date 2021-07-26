In this problem, it is proposed to implement the Bellman-Ford algorithm for finding all the shortest paths from a given vertex to the rest in a directed graph.
Input format
The input of the program is information about a connected directed weighted graph in the following format:

The first line contains two integers N and M, where N is the number of vertices and M is the number of arcs in the graph.
All N vertices are numbered, numbered from 0 to N-1, that is, the first vertex is numbered (0), and the last (N-1).
In the next M lines, there will be 3 numbers each: A B W, where A and B are the numbers of the vertices that the arc connects (the path from A to B), and W is the cost (weight) of the arc.

Restrictions: 2 <= N <= 1500, 1 <= M <= 30,000, -30000 <= W <= 30,000.
It is guaranteed that the original graph is connected.
The weights of arcs can be negative, the graph can contain negative cycles (see example 3).
One and the same pair of vertices is connected by at most two arcs of different orientations (for vertices u and v, there can be both an arc (u, v) and an arc (v, u)).

See example below.

Output format
All found shortest paths are output in the following format.
There are K lines in total, the first contains the number of paths (it is assumed that K = N-1 paths will be found).
In the next K lines, you need to output the length of the path to the vertex corresponding to the line number.
Since we start from the top # 0, then in the 1st line we need to output the length of the path to the top # 1, in the second line to the top # 2 ... and so on up to K.
See example below.

Example:
Input:
6 13
0 2 5
1 0 7
1 5 11
2 4 4
2 5 1
3 1 10
3 2 9
3 4 3
3 5 2
4 2 8
5 0 13
5 3 12
5 4 6

Output:
5
28
5
18
9
6
