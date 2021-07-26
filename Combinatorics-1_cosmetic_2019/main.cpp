#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

BigInteger factorial(int n) {
    BigInteger res(n);
    BigInteger temp(n);
    for (int i = 1; i < n; ++i) {
        temp.operator--();
        res.operator*=(temp);
    }
    return res;
}

void generate_(vector<int> &vector) {
    generate(vector.begin(), vector.end(), [] {
        static int i = 1;
        return i++;
    });
}

static int getShade(int N, BigInteger &k_, BigInteger &nFac) {
    for (int j = 1; j < N + 1; ++j) {
        if (nFac * j > k_) {
            return j;
        }
    }
}

string getString(vector<int> &vector) {
    string s;
    for (int item : vector) {
        s += to_string(item) + " ";
    }
    return s.substr(0, s.length() - 1);
}

static string get_day(int N, int k) {
    vector<int> shades(N);
    generate_(shades);
    BigInteger k_(k - 1);
    BigInteger nFac = factorial(N);
    vector<int> vRes;
    int shade = 0;

    for (int i = 0; i < N - 1; ++i) {
        nFac /= (N - i);
        shade = getShade(N, k_, nFac);
        k_ %= nFac;
        vRes.push_back(shades[shade - 1]);
        shades.erase(shades.begin() + (shade - 1));
    }
    vRes.push_back(shades[0]);

    return getString(vRes);
}

int main(int argc, const char *argv[]) {

    int N, K;
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
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
