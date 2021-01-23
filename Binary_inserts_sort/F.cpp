#include <iostream>
#include <vector>

using namespace std;

// fills the vector
void fillVector(vector<int>* vector);
// sorts vec using binary inserts sort alg and return the minimum number of shifts of 
// adjacent elements happend while sorting the vector
int binaryInsertsSort(vector<int>* vec);

int main()
{
	int N;
	cin >> N;
	vector<int> vec(N);
	fillVector(&vec);
	int shiftNum = binaryInsertsSort(&vec);
	for (auto const& item : vec)
		cout << item << " ";
	cout << endl;
	cout << shiftNum;
}

void fillVector(vector<int>* vector) {
	int number;
	for (int i = 0; i < (*vector).size(); i++)
	{
		cin >> number;
		(*vector)[i] = number;
	}
}

int binaryInsertsSort(vector<int>* vec) {
	int left, right, middle, k, p;
	int shiftNum = 0;
	for (int i = 1; i < (*vec).size(); i++)
	{
		if ((*vec)[i - 1] <= (*vec)[i])
			continue;

		left = 0;
		right = i - 1;
		middle = (left + right) / 2;
		/*
		 * finding the interval in which the considered element of the array falls
		 */
		while (left != middle)
		{
			if ((*vec)[middle] > (*vec)[i])
				right = middle - 1;
			else
				left = middle;
			middle = (left + right) / 2;
		}

		/*
		 * determining where to insert
		 */
		if ((*vec)[left] <= (*vec)[i]) {
			if ((*vec)[right] <= (*vec)[i])
				left = right + 1;
			else
				left = right;

		}

		k = i;
		p = (*vec)[i];
		/*
		 * shifting elements
		 */
		while (k > left)
		{
			/*
			 * to calculate the minimum number of shifts of adjacent elements
			 */
			if ((*vec)[k - 1] != p) {
				(*vec)[k] = (*vec)[k - 1];
				shiftNum++;
			}
			k--;
		}
		//Insert current element
		(*vec)[left] = p;
	}
	return shiftNum;
}