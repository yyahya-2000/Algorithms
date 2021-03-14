class CountingSort
{
private:
	//max between array elements
	int getMax(int* numbers, int array_size) {
		int max = *numbers;
		for (int i = 1; i < array_size; i++)
			if (*(numbers + i) > max)
				max = *(numbers + i);
		return max;
	}
	//min between array elements
	int getMin(int* numbers, int array_size) {
		int min = *numbers;
		for (int i = 1; i < array_size; i++)
			if (*(numbers + i) < min)
				min = *(numbers + i);
		return min;
	}

public:
	void countingSort(int* numbers, int array_size)
	{
		int max = getMax(numbers, array_size);
		int min = getMin(numbers, array_size);

		int auxiliaryArrayLenght = max - min + 1;

		int* auxiliary = new int[auxiliaryArrayLenght];
		int* res = new int[array_size];

		for (int i = 0; i < auxiliaryArrayLenght; i++)
			*(auxiliary + i) = 0;

		for (int i = 0; i < array_size; i++)
			(*(auxiliary + *(numbers + i) - min))++;

		for (int i = 1; i < auxiliaryArrayLenght; i++)
			*(auxiliary + i) += *(auxiliary + i - 1);

		for (int i = array_size - 1; i >= 0; i--)
		{
			*(res + *(auxiliary + *(numbers + i) - min) - 1) = *(numbers + i);
			(*(auxiliary + *(numbers + i) - min))--;
		}

		for (int i = 0; i < array_size; i++)
			*(numbers + i) = *(res + i);
		delete[] res;
		delete[] auxiliary;
	}
};