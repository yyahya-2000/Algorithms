#include "ReadWriter.cpp"
#include <algorithm>

using namespace std;

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node> &graph, int start, std::vector<std::string> &result) {
    vector<string> neighbours;
    vector<Node *> parents;
    parents.push_back(&graph[start]);
    int size_begin = 0;
    int size_end;
    result.push_back(graph[start].name);
    graph[start].visited = true;

    while (true) {
        size_end = parents.size();
        for (int i = size_begin; i < size_end; ++i) {
            for (auto &neighbour : parents[i]->neighbours) {
                if (!neighbour->visited) {
                    neighbours.push_back(neighbour->name);
                    neighbour->visited = true;
                    parents.push_back(neighbour);
                }
            }
        }
        if (neighbours.empty())
            break;

        sort(neighbours.begin(), neighbours.end(),
             [](const string &neighbour_1, const string &neighbour_2) { return neighbour_1 < neighbour_2; });

        for (const auto &i : neighbours) {
            result.push_back(i);
        }
        neighbours.clear();

        size_begin = size_end;
    }
}

int main() {
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}