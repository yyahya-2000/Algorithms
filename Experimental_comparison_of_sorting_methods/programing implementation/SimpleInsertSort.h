#include<vector>
using namespace std;

class SimpleInsertsSort
{
public:
	void simpleInsertsSort(int* arr, int n) {

		int b, j;
		for (int i = 1; i < n; i++)
		{
			b = arr[i];
			j = i - 1;
			while (j >= 0 && b < arr[j]) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = b;
		}
	}
};