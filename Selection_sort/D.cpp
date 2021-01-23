#include <iostream>
#include <vector>

using namespace std;

// fills the vector
void fillVector(vector<int>* vector);
// sorts vec using selection sort alg and return the num of swaps that occurred during the operation
int selectionSort(vector<int>* vec);

int main()
{
	int N;
	cin >> N;
	vector<int> vec(N);
	fillVector(&vec);
	int swapNum = selectionSort(&vec);
	for (auto const& item : vec)
		cout << item << " ";
	cout << endl;
	cout << swapNum;
}

int selectionSort(vector<int>* vec) {
	int swapNum = 0;
	int length = (*vec).size();
	int minInd;
	for (int i = 0; i < length - 1; i++) {
		minInd = i;
		for (int j = i + 1; j <= length - 1; j++)
			if ((*vec)[j] < (*vec)[minInd]) {
				minInd = j;

			}
		if ((*vec)[i] != (*vec)[minInd]) {
			swapNum++;
			swap((*vec)[i], (*vec)[minInd]);
		}

	}
	return swapNum;
}

void fillVector(vector<int>* vector) {
	int number;
	for (int i = 0; i < (*vector).size(); i++)
	{
		cin >> number;
		(*vector)[i] = number;
	}
}