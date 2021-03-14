#include<vector>
#include <random>
#include "QuickSortMiddlePivot.h"

using namespace std;

class ArrayGenerator
{
private:
	// reverse array
	void reverse(int* arr, int n)
	{
		int temp;
		for (int i = 0; i < n / 2; i++)
		{
			temp = arr[i];
			arr[i] = arr[n - i - 1];
			arr[n - i - 1] = temp;
		}
	}
	// revers array partially
	void partiallyReverse(int* arr, int n) {
		int elementsNum = n / 10;
		int temp;
		for (int i = 1; i < elementsNum; i += 2)
		{
			temp = arr[(i - 1) * 10];
			arr[(i - 1) * 10] = arr[i * 10];
			arr[i * 10] = temp;
		}
	}

public:
	// generate array by its type
	void generateArray(int* arr, int n, int type) {
		MyQuickSort qs;
		random_device dev;
		mt19937 rng(dev());
		switch (type)
		{
	    //first type
		case 1:
		{
			uniform_int_distribution<mt19937::result_type> dist_1(0, 5); // distribution in range [0, 5]
			for (int i = 0; i < n; i++)
				arr[i] = dist_1(rng);
		}
		break;
		//second type
		case 2:
		{
			uniform_int_distribution<mt19937::result_type> dist_2(0, 4000); // distribution in range [0, 4000]
			for (int i = 0; i < n; i++)
				arr[i] = dist_2(rng);
		}
		break;
		//third type
		case 3:
		{
			uniform_int_distribution<mt19937::result_type> dist_3(0, 4000); // distribution in range [0, 4000]
			for (int i = 0; i < n; i++)
				arr[i] = dist_3(rng);
			qs.quickSort(arr, n);
			partiallyReverse(arr, n);
		}
		break;
		// 4th type
		case 4:
		{
			uniform_int_distribution<mt19937::result_type> dist_4(1, 4100); // distribution in range [1, 4100]
			for (int i = 0; i < n; i++)
				arr[i] = dist_4(rng);
			qs.quickSort(arr, n);
			reverse(arr, n);
		}
		break;
		}
	}
};