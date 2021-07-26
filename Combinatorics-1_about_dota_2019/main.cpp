#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

//Необходимо реализовать 3 метода (1,2,3).
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static BigInteger FactTree(int n) //1
{
    BigInteger bigInteger(n);
    BigInteger temp(n);
    for (int i = 1; i < n; ++i) {
        temp.operator--();
        bigInteger.operator*=(temp);
    }
    return bigInteger;
}

static BigInteger C(int n, int k) //2
{
    BigInteger bigInteger(n);
    BigInteger temp(n);
    for (int i = 1; i < k; ++i) {
        temp.operator--();
        bigInteger.multiply(bigInteger, temp);
    }
    bigInteger = bigInteger.operator/(FactTree(k));
    return bigInteger;
}

//n!/((n/2)!*2^(n/2))
static BigInteger Pair(int n) //3
{
    BigInteger result = FactTree(n);
    result.operator/=(FactTree(n/2));
    BigInteger _2 = FactTree(2);
    for (int i = 0; i < n/2 ; ++i) {
        result.operator/=(_2);
    }
    return result;
}

int main(int argc, const char *argv[]) {

    int n, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open()) {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        n = N;
        getline(fin, str);
        K = atoi(str.c_str());
        fout << FactTree(N) << endl;
        fout << C(N, K) << endl;
        fout << Pair(N) << endl;
        fout.close();
        fin.close();
    }
    return 0;
}
