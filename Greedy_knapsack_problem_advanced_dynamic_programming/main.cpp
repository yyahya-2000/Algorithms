#include "ReadWriter.h"

using namespace std;



//Задача реализовать этот метод (жадный алгоритм)
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int> *items, vector<pair<int, int>> &res) {
    //copy items into vector
    vector<pair<int, int>> itemsVec;
    for (int i = 0; i < N; ++i) {
        itemsVec.push_back(items[i]);
    }

    // sort items
    sort(itemsVec.begin(), itemsVec.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
        if (lhs.second / (double) lhs.first == rhs.second / (double) rhs.first) {
            return lhs.first > rhs.first;
        }
        return lhs.second / (double) lhs.first > rhs.second / (double) rhs.first;
    });

    int weightSum = 0;
    for (int i = 0; i < N; ++i) {

        if (weightSum + itemsVec[i].first <= W){
            res.push_back(itemsVec[i]);
            weightSum += itemsVec[i].first;
        }
    }
}

int main(int argc, const char *argv[]) {
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество элементов, и у объекта всего 2 характеристики
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