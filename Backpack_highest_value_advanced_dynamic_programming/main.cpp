#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ReadWriter {
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter() {
        fin.close();
        fout.close();
    }

    ReadWriter() {
        fin.open("input.txt", std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    // read 1 int value and empty line
    int readInt() {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        int n;
        fin >> n;
        return n;
    }

    //read data in arr, arr should be initialized before this method
    void readArr(int *arr, int n) {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        for (int i = 0; i < n; i++)
            fin >> arr[i];
    }


    void writeInt(int a) {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << a << "\n";
    }
};


int calculateMaxPrice(int *pInt, int *pInt1, int n, int w);

int main() {
    ReadWriter readWriter;
    int *M;
    int *C;
    int N;
    int W;

    N = readWriter.readInt();
    W = readWriter.readInt();

    M = new int[N];
    C = new int[N];
    readWriter.readArr(M, N);
    readWriter.readArr(C, N);

    readWriter.writeInt(calculateMaxPrice(M, C, N, W));
    delete[] M;
    delete[] C;

    return 0;
}

void cleanMemory(int **table, int N) {
    for (int i = 0; i <= N; ++i)
        delete[] table[i];
    delete[] table;
}

int calculateMaxPrice(int *M, int *C, int N, int W) {
    int **table = new int *[N + 1];
    for (int i = 0; i <= N; ++i)
        table[i] = new int[W + 1];
    for (int i = 0; i <= N; ++i)
        table[i][0] = 0;
    for (int i = 0; i <= W; ++i)
        table[0][i] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int q = 1; q <= W; ++q) {
            table[i][q] = (M[i - 1] <= q) ?
                          max(table[i - 1][q], (table[i - 1][q - M[i - 1]] + C[i - 1])) :
                          table[i - 1][q];
        }
    }
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <=W ; ++j) {
            cout << table[i][j]<<" ";
        }
        cout<<endl;
    }

    int res = table[N][W];
    cleanMemory(table, N);
    return res;
}
