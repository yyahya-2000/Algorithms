In this problem, it is proposed to implement the Floyd-Warshall algorithm for finding the shortest paths between all pairs of vertices in a directed graph.

Input format
The input of the program is information about a connected directed weighted graph in the following format:

In the first line, the number N is the number of vertices, in the second line M is the number of edges in the graph. All N vertices are numbered, numbered from 0 to N-1. Each of the next M lines contains 3 numbers: A B W, where A and B are the numbers of the vertices that the arc connects, and W is the weight of the arc.

Restrictions: 2 <= N <= 500, 1 <= M <= 130000, 0 <= W <= 130000.
The weights of all arcs are non-negative, the same pair of vertices is connected by at most two arcs of different orientations (for vertices u and v, there can be both an arc (u, v) and an arc (v, u)).

It is guaranteed that the original graph is connected.
See example below.

Output format
All found shortest paths are output in the following format.
each line contains three components: A B C, where
A - the number of the vertex from which the path leads,
B is the number of the vertex to which the path leads,
C - weight of the found path,
When outputting paths, the numbers of vertices are displayed in lexicographic order (i.e., the first is the path from vertex 1 to vertex 2, the second is from vertex 1 to vertex 3, etc.).
Recall that the path from vertex 1 to vertex 2 does not necessarily coincide with the path from 2 to 1 (directed graph). Thus, the response should contain | V | * (| V | -1) lines, if | V | - the number of vertices in the original graph.
If the path to any vertex cannot be found (due to the orientation of the arcs), the corresponding line has the format: A B -1, where A is the number of the vertex from which no path could be found,
B - the number of the vertex to which the path could not be found.

See example below.

Example:
Input:
4
6
0 1 4
0 2 6
0 3 3
1 2 9
3 1 1
2 3 7

Output:
0 1 4
0 2 6
0 3 3
1 0 -1
1 2 9
1 3 16
2 0 -1
2 1 8
2 3 7
3 0 -1
3 1 1
3 2 10
