#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// returns length of the longest common subsequence of strings X and Y
int getLCS(string &x, string &y) {
    int len_x = x.length();
    int len_y = y.length();
    int res;
    //initializing the two dimension array
    int **dp = new int *[len_x + 1];
    for (int l = 0; l < len_x + 1; l++) {
        dp[l] = new int[len_y + 1];
        for (int i = 0; i < len_y + 1; ++i) {
            dp[l][i] = 0;
        }
    }

    //processing the result
    for (int i = 1; i < len_x + 1; i++) {
        for (int j = 1; j < len_y + 1; j++) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    //cleaning the memory
    res = dp[len_x][len_y];
    for (int i = 0; i < len_x + 1; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    return res;
}

int main() {
    string x;
    string y;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}