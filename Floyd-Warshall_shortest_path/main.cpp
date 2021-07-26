#include "ReadWriter.h"

using namespace std;
const int INF = INT32_MAX;

void ReadWriter::writeValues(std::vector<std::vector<int>> result) {
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            if (i != j) {
                if (result[i][j] == INF)
                    fout << i << " " << j << " " << -1 << '\n';
                else
                    fout << i << " " << j << " " << result[i][j] << '\n';
            }
        }
    }
}


void solve(int N, int M, vector<Edge> &edges, vector<vector<int>> &matrix) {
    //  for (int i = 0; i < N; ++i) {
    //      matrix[i].assign(N, INF);
    //      matrix[i][i] = 0;
    //      if (i < M)
    //          matrix[edges[i].A][edges[i].B] = edges[i].W;
    //  }
    for (int j = 0; j < M; ++j) {
        if (matrix[edges[j].A].empty()) {
            matrix[edges[j].A].assign(N, INF);
            matrix[edges[j].A][edges[j].A] = 0;
        }
        matrix[edges[j].A][edges[j].B] = edges[j].W;
    }

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (matrix[i][k] < INF && matrix[k][j] < INF)
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);

}

int main() {
    ReadWriter rw;

    int N, M;
    rw.read2Ints(N, M);

    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<vector<int>> result(N);

    solve(N, M, edges, result);

    rw.writeValues(result);

    return 0;
}