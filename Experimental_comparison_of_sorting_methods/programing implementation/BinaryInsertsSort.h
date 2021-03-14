#include<vector>
using namespace std;

class BinaryInsertsSort
{
public:
	void binaryInsertsSort(int* arr, int n) {
		int left, right, middle, k, p;
		for (int i = 1; i < n; i++)
		{
			if (arr[i - 1] <= arr[i])
				continue;

			left = 0;
			right = i - 1;
			middle = (left + right) / 2;
			/*
			 * finding the interval in which the considered element of the array falls
			 */
			while (left != middle)
			{
				if (arr[middle] > arr[i])
					right = middle - 1;
				else
					left = middle;
				middle = (left + right) / 2;
			}

			/*
			 * determining where to insert
			 */
			if (arr[left] <= arr[i]) {
				if (arr[right] <= arr[i])
					left = right + 1;
				else
					left = right;

			}

			k = i;
			p = arr[i];
			/*
			 * shifting elements
			 */
			while (k > left)
			{
				/*
				 * to calculate the minimum number of shifts of adjacent elements
				 */
				if (arr[k - 1] != p) {
					arr[k] = arr[k - 1];
				}
				k--;
			}
			//Insert current element
			arr[left] = p;
		}
	}

};

