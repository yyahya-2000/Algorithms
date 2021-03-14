#include <iostream>
#include <fstream>

class Heapsort
{
private:
	int heapSize;
	// heapify the sub-tree
	void heapify(int* nums, int i)
	{
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		/*
		* finding the largest
		*/
		if (left < heapSize && *(nums + left) > *(nums + largest))
			largest = left;
		if (right < heapSize && *(nums + right) > *(nums + largest))
			largest = right;
		// if the largest isn't the parent vertex
		if (largest != i) {
			swap(*(nums + i), *(nums + largest));
			heapify(nums, largest);
		}
	}
public:

	//Функция сортировки на куче
	void heapSort(int* numbers, int array_size)
	{
		/*
		 * building heap
		 */
		heapSize = array_size;
		for (int i = array_size / 2 - 1; i >= 0; i--)
			heapify(numbers, i);
		// heap sorting
		for (int i = array_size - 1; i >= 0; i--)
		{
			swap(*(numbers), *(numbers + i));
			heapSize--;
			heapify(numbers, 0);
		}
	}
};