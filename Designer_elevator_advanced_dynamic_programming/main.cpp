#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
        //empty line read
        std::string s;
        std::getline(fin, s);
        return n;
    }

    //read data in arr, arr should be initialized before this method
    void readVec(vector<int> &vec, int n) {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        int temp;
        for (int i = 0; i < n; i++) {
            fin >> temp;
            vec.push_back(temp);
        }
    }


    void writeInt(int a) {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << a << "\n";
    }
};

int adequacyAssessment(vector<int> &ABC, int N);

int main() {
    ReadWriter readWriter;
    vector<int> ABC;
    int N;

    N = readWriter.readInt();

    readWriter.readVec(ABC, 3);

    readWriter.writeInt(adequacyAssessment(ABC, N));
    return 0;
}

int adequacyAssessment(vector<int> &ABC, int N) {
    sort(ABC.begin(), ABC.end());

    vector<bool> res(N);
    res[0] = true;
    int count = 1;

    for (int i = ABC[0] + 1; i <= N; ++i) {
        for (int btnNum : ABC) {
            if (!res[i - 1]) {
                if ((i - 1 - btnNum >= 0 && res[i - 1 - btnNum])) {
                    res[i - 1] = true;
                    count++;
                }
            }
        }
    }

    return count;
}
