#include "ReadWriter.h"

using namespace std;

void cleanMemory(int **dp, int N) {
    for (int i = 0; i <= N; ++i)
        delete[] dp[i];
    delete[] dp;
}

// getting the result from the two dimension array which we already have
void concludeRes(int N, int W, int **dp, int *stones, vector<int> &res) {
    int i = N, j = W;
    for (;;) {
        if (dp[i][j] != dp[i - 1][j]) {
            j = dp[i][j] - stones[i - 1];
            res.insert(res.begin(), stones[i - 1]);
        }
        i--;
        if (i <= 0 || j <= 0)
            break;
    }
}

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int *stones, vector<int> &res) {
    int **dp = new int *[N + 1];
    for (int i = 0; i <= N; ++i)
        dp[i] = new int[W + 1]{};

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= W; ++j)
            if (j >= stones[i - 1])
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            else
                dp[i][j] = dp[i - 1][j];

    concludeRes(N, W, dp, stones, res);

    cleanMemory(dp, N);
}

int main(int argc, const char *argv[]) {
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int *arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}