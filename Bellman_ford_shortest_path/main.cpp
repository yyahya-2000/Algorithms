#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h


using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge> &edges, vector<int> &result) {
    const int INF = INT32_MAX;
    result.assign(N, INF);
    result[0] = 0;
    bool any;
    for (int i = 0; i < N; ++i) {
        any = false;
        for (int i = 0; i < M; ++i) {
            if (result[edges[i].A] < INF && result[edges[i].B] > result[edges[i].A] + edges[i].W) {
                result[edges[i].B] = result[edges[i].A] + edges[i].W;
                any = true;
            }
        }

        if (!any)
            break;
    }
    result.erase(result.begin());
    if (any) {
        result.clear();
    }

}

int main() {
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    if (!result.empty()) {
        //Выводим результаты
        rw.writeInt(result.size());
        rw.writeIntValues(result);
    }

    return 0;
}