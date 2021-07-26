#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

vector<long long> getResVec(long long k, long long n) {
    vector<long long> result;
    long long nn = n;
    long long temp;
    while (k >= n) {
        temp = k % n;
        k /= n;
        n--;
        result.push_back(temp + 1);
    }

    result.push_back(k + 1);

    int size = result.size();
    for (int i = 0; i < nn - size; ++i)
        result.push_back(1);

    return result;
}

string getString(vector<long long> &vector) {
    string str;
    for (long long item : vector) {
        str += to_string(item) + " ";
    }
    return str.substr(0, str.length() - 1);
}

static string getRes(long long n, long long k) {
    vector<long long> result = getResVec(k - 1, n);

    reverse(result.begin(), result.end());

    return getString(result);
}


int main(int argc, const char *argv[]) {

    long long N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    string s;
    if (fin.is_open()) {
        getline(fin, s);
        N = strtol(s.c_str(), nullptr, 10);
        getline(fin, s);
        K = strtol(s.c_str(), nullptr, 10);

        fout << getRes(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
