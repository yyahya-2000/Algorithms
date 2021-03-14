#pragma once
#include <fstream>

class MyQuickSort
{
private:
	void originalQuickSort(int* nums, int left, int right) {
		int i = left;
		int j = right;
		int indPivod = (i + j) / 2;
		int pivot = *(nums + indPivod);
		while (true)
		{
			while (*(nums + i) < pivot)
				i++;
			while (*(nums + j) > pivot)
				j--;
			if (i <= j) {
				std::swap(*(nums + i), *(nums + j));
				i++;
				j--;
			}
			if (!(i <= j))
				break;
		}
		if (left < j) {
			originalQuickSort(nums, left, j);
		}
		if (right > i)
		{
			originalQuickSort(nums, i, right);
		}
	}
public:
	void quickSort(int* nums, int n) {
		originalQuickSort(nums, 0, n - 1);
	}

};