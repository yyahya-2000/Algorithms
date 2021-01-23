#include <iostream>
#include <vector>

using namespace std;

// fills the vector
void fillVector(vector<int>* vector);
// sorts vec using bubble alg and return the num of swaps that occurred during the operation
int bubbleSort(vector<int>* vec);

int main()
{
	int N;
	cin >> N;
	vector<int> vec(N);
	fillVector(&vec);
	int swapNum = bubbleSort(&vec);
	for (auto const& item : vec)
		cout << item << " ";
	cout << endl;
	cout << swapNum;

}

void fillVector(vector<int>* vector) {
	int number;
	for (int i = 0; i < (*vector).size(); i++)
	{
		cin >> number;
		(*vector)[i] = number;
	}
}

int bubbleSort(vector<int>* vec) {
	int bound = (*vec).size() - 1;
	int i, t;
	int swapNum = 0;
	while (1)
	{
		t = 0;
		for (i = 0; i < bound; i++)
		{
			if ((*vec)[i] > (*vec)[i + 1]) {
				swap((*vec)[i], (*vec)[i + 1]);
				t = i;
				swapNum += 1;
			}
		}
		if (t == 0)
			break;
		bound = t;
		i = 0;
	}
	return swapNum;
}