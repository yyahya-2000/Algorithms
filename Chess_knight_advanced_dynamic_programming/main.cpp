#include "ReadWriter.h"

using namespace std;


int MM, NN;

long long doIt(int n, int m, long long **chessBoard) {

    if (n < 0 || n > NN || m < 0 || m > MM)
        return 0;
    if (chessBoard[n][m] == -1) {
        chessBoard[n][m] =
                doIt(n - 2, m - 1, chessBoard) + doIt(n - 2, m + 1, chessBoard) + doIt(n - 1, m - 2, chessBoard) +
                doIt(n + 1, m - 2, chessBoard);
    }
    return chessBoard[n][m];


}
//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M) {
    auto **chessBoard = new long long *[N];
    for (int i = 0; i < N; ++i) {
        chessBoard[i] = new long long[M];
        for (int j = 0; j < M; ++j) {
            chessBoard[i][j] = -1;
        }
    }
   chessBoard[0][0] = 1;

    NN = N - 1;
    MM = M - 1;
    long long res = doIt(N - 1, M - 1, chessBoard);

    for (int i = 0; i < N; ++i)
        delete[] chessBoard[i];
    delete[] chessBoard;

    return res;
}



int main(int argc, const char *argv[]) {
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}
/*
 *
 *
 *   if ((n - 2 != 0 || m - 1 != 0) && n - 2 >= 0 && m - 1 >= 0 && n - 2 <= NN && m - 1 <= MM &&
        ChessBoard[n - 2][m - 1] == -1)
        doIt(n - 2, m - 1);
    if (((n - 2 != 0 || m + 1 != 0)) && n - 2 >= 0 && m + 1 >= 0 && n - 2 <= NN && m + 1 <= MM &&
        ChessBoard[n - 2][m + 1] == -1)
        doIt(n - 2, m + 1);
    if (((n - 1 != 0 || m - 2 != 0)) && n - 1 >= 0 && m - 2 >= 0 && n - 1 <= NN && m - 2 <= MM &&
        ChessBoard[n - 1][m - 2] == -1)
        doIt(n - 1, m - 2);
    if (((n + 1 != 0 || m - 2 != 0)) && n + 1 >= 0 && m - 2 >= 0 && n + 1 <= NN && m - 2 <= MM &&
        ChessBoard[n + 1][m - 2] == -1)
        doIt(n + 1, m - 2);

    //  cout << n << "  " << m << endl;
    ChessBoard[n][m] =
            ((n - 2 >= 0 && m - 1 >= 0 && n - 2 <= NN && m - 1 <= MM) ? ((n - 2 == 0 && m - 1 == 0) ? 1 : (
                    ChessBoard[n - 2][m - 1] == -1 ? 0 : ChessBoard[n - 2][m - 1])) : 0) +
            ((n - 2 >= 0 && m + 1 >= 0 && n - 2 <= NN && m + 1 <= MM) ? ((n - 2 == 0 && m + 1 == 0) ? 1 : (
                    ChessBoard[n - 2][m + 1] == -1 ? 0 : ChessBoard[n - 2][m + 1])) : 0) +
            ((n - 1 >= 0 && m - 2 >= 0 && n - 1 <= NN && m - 2 <= MM) ? ((n - 1 == 0 && m - 2 == 0) ? 1 : (
                    ChessBoard[n - 1][m - 2] == -1 ? 0 : ChessBoard[n - 1][m - 2])) : 0) +
            ((n + 1 >= 0 && m - 2 >= 0 && n + 1 <= NN && m - 2 <= MM) ? ((n + 1 == 0 && m - 2 == 0) ? 1 : (
                    ChessBoard[n + 1][m - 2] == -1 ? 0 : ChessBoard[n + 1][m - 2])) : 0);*/