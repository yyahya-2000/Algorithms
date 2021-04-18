#include "ReadWriter.cpp"
#include <algorithm>

using namespace std;

void solve_req(Node &person, vector<string> &result);

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node> &graph, int start, std::vector<std::string> &result) {
    for (Node &person : graph) {
        sort(person.neighbours.begin(), person.neighbours.end(),
             [](Node *neighbour_1, Node *neighbour_2) { return neighbour_1->name < neighbour_2->name; });
    }
    solve_req(graph[start], result);
}

void solve_req(Node &person, vector<std::string> &result) {
    if (person.visited)
        return;
    person.visited = true;
    result.push_back(person.name);
    for (Node *neighbour : person.neighbours)
        solve_req(*neighbour, result);
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