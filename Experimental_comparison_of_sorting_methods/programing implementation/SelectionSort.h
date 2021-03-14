#include <vector>

using namespace std;
class SelectionSort
{
public:
	void selectionSort(int* vec, int n) {
		int minInd;
		for (int i = 0; i < n - 1; i++) {
			minInd = i;
			for (int j = i + 1; j <= n - 1; j++)
				if (vec[j] < vec[minInd]) 
					minInd = j;
			if (vec[i] != vec[minInd]) 
				swap(vec[i], vec[minInd]);
		}
	}
};