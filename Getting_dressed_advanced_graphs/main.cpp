#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> visited;
vector<string> components;

void dfs(vector<vector<bool>>& relations, vector<string>& names, int vertexIndex)
{
    vector<pair<int, string>> orderDetour;

    for (int j = 0; j < relations[0].size(); ++j)
        if(relations[vertexIndex][j] && !visited[vertexIndex])
            orderDetour.emplace_back(j, names[j]);

    sort(orderDetour.begin(), orderDetour.end() , [](const pair<int, string>& vertex_1, const pair<int, string>& vertex_2) {
        return vertex_1.second < vertex_2.second;
    });

    for (int i = 0; i < orderDetour.size(); ++i)
        dfs(relations, names, orderDetour[i].first);

    if(!visited[vertexIndex])
    {
        components.push_back(names[vertexIndex]);
        visited[vertexIndex] = true;
    }
}

vector<string> getList(vector<string>& names, vector<vector<bool>>& relation)
{
    int n = names.size();
    vector<pair<int, string>> orderDetour;
    visited =  vector<bool>(n);

    bool isSrcVertex;
    for (int i = 0; i < n; i++)
    {
        isSrcVertex = true;
        for (int j = 0; j < relation[i].size() ; ++j)
            if(relation[j][i]){
                isSrcVertex = false;
                break;
            }

        if (isSrcVertex)
            orderDetour.emplace_back(i, names[i]);
    }

    sort(orderDetour.begin(), orderDetour.end() , [](const pair<int, string>& vertex_1, const pair<int, string>& vertex_2) {
        return vertex_1.second < vertex_2.second;
    });

    for (int i = 0; i < orderDetour.size(); ++i) {
        dfs(relation, names, orderDetour[i].first);
    }

    reverse(components.begin(), components.end());

    return components;
}


int main()
{
    vector<string> names;
    vector<vector<bool>> relations;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }
        relations = vector<vector<bool>>(names.size());
        for (int i = 0; i < names.size(); i++)
        {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }
        getline(fin, str);
        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }
        fin.close();
    }

    vector<string> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (auto& re : res)
        fout << re << "\n";
    fout.close();
    return 0;
}