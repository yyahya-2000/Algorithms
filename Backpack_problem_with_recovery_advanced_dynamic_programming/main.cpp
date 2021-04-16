#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

void buildTable(int N, int W, pair<int, int> *items, int **table) {
    for (int i = 0; i <= N; ++i)
        table[i][0] = 0;
    for (int i = 0; i <= W; ++i)
        table[0][i] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int q = 1; q <= W; ++q) {
            table[i][q] = (items[i - 1].first <= q) ?
                          max(table[i - 1][q], (table[i - 1][q - items[i - 1].first] + items[i - 1].second)) :
                          table[i - 1][q];
        }
    }
}

void cleanMemory(int **table, int N) {
    for (int i = 0; i <= N; ++i)
        delete[] table[i];
    delete[] table;
}

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int> *items, vector<pair<int, int>> &res) {
    int **table = new int *[N + 1];
    for (int i = 0; i <= N; ++i)
        table[i] = new int[W + 1];

    buildTable(N, W, items, table);

    int i = N, j = W;
    while (true) {
        if (table[i][j] != table[i - 1][j]) {
            res.push_back(items[i - 1]);
            j -= items[i - 1].first;
            i--;
        } else {
            i--;
        }
        if (table[i][j] == 0)
            break;
    }

    cleanMemory(table, N);

}

int main(int argc, const char *argv[]) {
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int> *arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++) {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}