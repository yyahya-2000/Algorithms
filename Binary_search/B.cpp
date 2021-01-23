#include <iostream>
#include <vector>
#include <string>

using namespace std;
//filling the vectors
void fillVector(vector<int>* vector);
//binary search of b in A vector
bool binarySearch(vector<int>* A, int b);

int main()
{
	int N, K;
	cin >> N >> K;
	vector<int> A(N), B(K);
	fillVector(&A);
	fillVector(&B);
	for (int i = 0; i < B.size(); i++) 
		cout << (binarySearch(&A, B[i]) ? "YES" : "NO") << endl;
}

void fillVector(vector<int>* vector) {
	int number;
	for (int i = 0; i < (*vector).size(); i++)
	{
		cin >> number;
		(*vector)[i] = number;
	}
}

bool binarySearch(vector<int>* A, int b) {
	int left = 0;
	int right = (*A).size() - 1;
	int ind = -1;
	int middle;
	while (left <= right && ind == -1)
	{
		middle = left + (right - left) / 2;
		if ((*A)[middle] == b)
			return true;
		else if ((*A)[middle] > b)
			left = middle + 1;
		else
			right = middle - 1;
	}
	return false;
}