#include "ReadWriter.h"

using namespace std;

void initializeMatrix(int N, vector<Edge> &edges, vector<vector<int>> &matrix) {
    for (int i = 0; i < N; ++i) {
        vector<int> row(N, 30000);
        matrix.push_back(row);
    }

    for (auto &edge : edges) {
        matrix[edge.A][edge.B] = edge.W;
        matrix[edge.B][edge.A] = edge.W;
    }
}

int isEdgeExist(vector<Edge> &edges, int a, int b) {
    for (int i = 0; i < edges.size(); ++i)
        if ((edges[i].A == a && edges[i].B == b) || (edges[i].B == a && edges[i].A == b))
            return i;
    return -1;
}

void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result) {
    vector<vector<int>> matrix;
    initializeMatrix(N, edges, matrix);
    vector<bool> used(N);

    vector<int> minElement(N, 30000), selected(N, -1);
    minElement[0] = 0;
    for (int i = 0; i < N; ++i) {
        int value = -1;
        for (int j = 0; j < N; ++j) {
            if (!used[j] && (value == -1 || minElement[value] > minElement[j]))
                value = j;
        }

        used[value] = true;
        if (selected[value] != -1) {
            result.push_back(edges[isEdgeExist(edges, value, selected[value])]);
        }

        for (int j = 0; j < N; ++j) {
            if (matrix[value][j] < minElement[j]) {
                minElement[j] = matrix[value][j];
                selected[j] = value;
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