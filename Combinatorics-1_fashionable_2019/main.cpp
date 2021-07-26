#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

BigInteger factorial(int n) {
    BigInteger bigInteger(n);
    BigInteger temp(n);
    for (int i = 1; i < n; ++i) {
        temp.operator--();
        bigInteger.operator*=(temp);
    }
    return bigInteger;
}

void generate_(vector<int> &vector) {
    generate(vector.begin(), vector.end(), [] {
        static int i = 1;
        return i++;
    });
}

int getSweater(int N, const BigInteger &k_, BigInteger &kr) {
    for (int i = 0; i < N; ++i)
        if (kr * (i + 1) > k_)
            return (i + 1);
}

string getString(vector<int> &vector) {
    string s;
    for (int item : vector) {
        s += to_string(item) + " ";
    }
    return s.substr(0, s.length() - 1);
}

string get(int N, int k, int m) {
    vector<int> sweaters(N);
    BigInteger k_(k - 1);
    BigInteger kRight = factorial(N) / factorial(N - m);;

    generate_(sweaters);
    int sweater = 0;
    vector<int> vResult;

    for (int i = 0; i < m; ++i) {
        kRight /= (N - i);
        sweater = getSweater(N, k_, kRight);
        k_ %= kRight;
        vResult.push_back(sweaters[sweater - 1]);
        sweaters.erase(sweaters.begin() + (sweater - 1));
    }

    return getString(vResult);
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