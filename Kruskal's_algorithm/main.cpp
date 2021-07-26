#include "ReadWriter.h"

using namespace std;

void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result) {
    sort(edges.begin(), edges.end(), [](Edge &left, Edge &right) { return left.W < right.W; });
    vector<int> treeType(N);
    int oldType, newType;

    for (int i = 0; i < N; ++i)
        treeType[i] = i;

    for (int i = 0; i < M; ++i) {
        if (treeType[edges[i].A] != treeType[edges[i].B]) {
            result.push_back(edges[i]);
            oldType = treeType[edges[i].B];
            newType = treeType[edges[i].A];
            for (int j = 0; j < N; ++j) {
                if (treeType[j] == oldType)
                    treeType[j] = newType;
            }
        }
    }
}

int main() {
    ReadWriter rw;
    int N, M;
    rw.read2Ints(N, M);

    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<Edge> result;

    solve(N, M, edges, result);

    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}

