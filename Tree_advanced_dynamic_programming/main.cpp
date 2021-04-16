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


void solve(vector<int> &levels, vector<int> &res) {
    if (levels.empty()) {
        return;
    }

    int level = *max_element(levels.begin(), levels.end());
    vector<int> pawsNumByLevel(level);
    pawsNumByLevel[0] = 0;
    pawsNumByLevel[1] = 0;
    pawsNumByLevel[2] = 4;
    pawsNumByLevel[3] = 4;
    int mod_ = 1000000007;

    for (int j = 4; j < level; ++j)
        pawsNumByLevel[j] = max(
                static_cast<int>((2 * static_cast<long long>(pawsNumByLevel[j - 2]) + pawsNumByLevel[j - 1]) % mod_),
                static_cast<int>(((2 * static_cast<long long>(pawsNumByLevel[j - 4])) % mod_ +
                                  (2 * pawsNumByLevel[j - 4]) % mod_ + (2 * pawsNumByLevel[j - 3]) % mod_ +
                                  (2 * pawsNumByLevel[j - 3]) % mod_ + pawsNumByLevel[j - 2] + 4) % mod_));

    for (int level_ : levels)
        res.push_back(pawsNumByLevel[level_ - 1]);


}


int main() {
    ReadWriter readWriter;
    vector<int> levels;
    vector<int> res;
    int N;
    N = readWriter.readInt();

    readWriter.readVec(levels, N);
    solve(levels, res);
    for (int re : res) {
        readWriter.writeInt(re);
    }

    return 0;
}
