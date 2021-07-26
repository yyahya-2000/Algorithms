#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void generate_(vector<int> &vector) {
    generate(vector.begin() + 1, vector.end(), [] {
        static int i = 1;
        return i++;
    });
}

string getString(vector<int> &vector) {
    string s;
    for (int i = 1; i < vector.size(); ++i) {
        s += to_string(vector[i]) + " ";
    }

    return s.substr(0, s.length() - 1);
}

static int getIndTask(vector<int> &tasks, int m, int N) {
    for (int i = m; i >= 1; --i)
        if (tasks[i] < N)
            return i;
}

static string get(int N, int k, int m) {
    vector<int> tasks(m + 1);
    generate_(tasks);
    int indTask;

    for (int j = 1; j < k; ++j) {
        indTask = getIndTask(tasks, m, N);
        ++tasks[indTask];
        for (int i = indTask + 1; i <= m; ++i)
            tasks[i] = tasks[i - 1] + 1;
    }
    return getString(tasks);
}


int main(int argc, const char *argv[]) {
    int M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open()) {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        getline(fin, str);
        K = atoi(str.c_str());
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get(N, K, M) << endl;

        fout.close();
        fin.close();
    }
    return 0;
}