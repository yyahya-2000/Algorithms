#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

stack<int> dfsStack;
vector<bool> visited;
vector<string> componentElements;


void sortComponents(vector<vector<string>> &components) {
    for (auto &i : components)
        sort(i.begin(), i.end());

    sort(components.begin(), components.end());
}

void dfs(int s, vector<vector<bool>> &relations) {
    visited[s] = true;
    for (int i = 0; i < relations[s].size(); ++i)
        if (relations[s][i] && !visited[i])
            dfs(i, relations);

    dfsStack.push(s);
}

void dfsBack(int vertex, vector<vector<bool>> &relations, vector<string> &names) {
    visited[vertex] = true;
    componentElements.push_back(names[vertex]);
    for (int i = 0; i < relations[vertex].size(); ++i)
        if (relations[i][vertex] && !visited[i])
            dfsBack(i, relations, names);
}

vector<vector<string>> getList(vector<string> &names, vector<vector<bool>> &relations) {
    vector<vector<string>> components;

    for (int i = 0; i < names.size(); ++i) {
        if (!visited[i])
            dfs(i, relations);
    }

    for (auto &&i : visited)
        i = false;

    int vertex;
    while (!dfsStack.empty()) {
        vertex = dfsStack.top();
        dfsStack.pop();
        if (!visited[vertex]) {
            dfsBack(vertex, relations, names);
            components.push_back(componentElements);
            componentElements.clear();
        }
    }

    sortComponents(components);

    return components;
}


int main() {
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        string str = "";
        getline(fin, str);
        while (str != "#") {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool >>(names.size());
        visited = vector<bool>(names.size());
        for (int i = 0; i < names.size(); i++) {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }
        getline(fin, str);
        while (fin) {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }
        fin.close();
    }

    vector<vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }

    fout.close();

    return 0;
}