#include <iostream>
#include <vector>

using namespace std;

// fills the vector
void fillVector(vector<int>* vector);
// sorts vec using simple inserts sort alg and return the number of elements 
// that were already in the right place while sorting
int simpleInsertsSort(vector<int>* vec);

int main()
{
	int N;
	cin >> N;
	vector<int> vec(N);
	fillVector(&vec);
	int swapNum = simpleInsertsSort(&vec);
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

int simpleInsertsSort(vector<int>* vec) {

	int length = (*vec).size();
	int b, j;
	bool wasMoved = false;
	int count = 0;
	for (int i = 1; i < length; i++)
	{
		b = (*vec)[i];
		j = i - 1;
		wasMoved = false;
		while (j >= 0 && b < (*vec)[j]) {
			(*vec)[j + 1] = (*vec)[j];
			j--;
			wasMoved = true;
		}
		if (!wasMoved) {
			count++;
			continue;
		}		
		(*vec)[j + 1] = b;
	}
	return count;
}