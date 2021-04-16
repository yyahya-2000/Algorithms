#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string &riverMap) {
    int res = 0;
    //0: left , 1: right
    int currentDir = 0;
    vector<char> withoutB;
    for (int i = 0; i < riverMap.length(); ++i) {
        if (riverMap[i] == 'B') {
            res++;
            continue;
        }
        withoutB.push_back(riverMap[i]);

    }
    for (int i = 0; i < withoutB.size(); ++i) {
        if (i == withoutB.size() - 1) {
            if (currentDir == 0) {
                if (withoutB[i] == 'L')
                    res += 1;
                else
                    res++;
            } else if (withoutB[i] == 'R') {
                res++;
            }
        } else if (currentDir == 0 && withoutB[i] == 'L' && withoutB[i + 1] == 'L') {
            currentDir = 1;
            res++;
        } else if (currentDir == 1 && withoutB[i] == 'R' && withoutB[i + 1] == 'R') {
            currentDir = 0;
            res++;
        } else if (currentDir == 0 && withoutB[i] == 'L') {
            res++;
        } else if (currentDir == 1 && withoutB[i] == 'R') {
            res++;
        }
    }
    return res;

}


int main() {
    string riverMap;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        getline(fin, riverMap);
        fin.close();
    }

    res = countMaxCross(riverMap);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
