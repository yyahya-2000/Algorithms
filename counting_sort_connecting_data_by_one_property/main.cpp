#include "ReadWriter.h"

using namespace std;

//function to get the min value between all values in "numbers"
int getMax(int* numbers, int array_size);

//function to get the max value between all values in "numbers"
int getMin(int* numbers, int array_size);

// Функция сортировки подсчетом
void countingSortById(int* droneIds, int* droneCarryingCapacities, int array_size)
{
	int max = getMax(droneCarryingCapacities, array_size);
	int min = getMin(droneCarryingCapacities, array_size);

	int auxiliaryArrayLenght = max - min + 1;

	int* auxiliary = new int[auxiliaryArrayLenght];
	int* resCarryingCapacities = new int[array_size];
	int* resIds = new int[array_size];

	for (int i = 0; i < auxiliaryArrayLenght; i++)
		*(auxiliary + i) = 0;

	for (int i = 0; i < array_size; i++)
		(*(auxiliary + *(droneCarryingCapacities + i) - min))++;

	for (int i = auxiliaryArrayLenght - 2; i >= 0; i--)
		*(auxiliary + i) += *(auxiliary + i + 1);

	for (int i = array_size - 1; i >= 0; i--)
	{
		*(resCarryingCapacities + *(auxiliary + *(droneCarryingCapacities + i) - min) - 1) = *(droneCarryingCapacities + i);
		*(resIds + *(auxiliary + *(droneCarryingCapacities + i) - min) - 1) = *(droneIds + i);
		(*(auxiliary + *(droneCarryingCapacities + i) - min))--;
	}

	for (int i = 0; i < array_size; i++) {
		*(droneCarryingCapacities + i) = *(resCarryingCapacities + i);
		*(droneIds + i) = *(resIds + i);
	}

	delete[] resCarryingCapacities;
	delete[] resIds;
	delete[] auxiliary;
}

int main()
{
	ReadWriter rw;


	int* droneIds = nullptr;
	int* droneCarryingCapacities = nullptr;
	int n;

	n = rw.readInt();

	droneIds = new int[n];
	droneCarryingCapacities = new int[n];

	rw.readArrays(droneIds, droneCarryingCapacities, n);

	countingSortById(droneIds, droneCarryingCapacities, n);

	rw.writeArrays(droneIds, droneCarryingCapacities, n);

	delete[] droneIds;
	delete[] droneCarryingCapacities;

	return 0;
}

int getMax(int* numbers, int array_size) {
	int max = *numbers;
	for (int i = 1; i < array_size; i++)
		if (*(numbers + i) > max)
			max = *(numbers + i);
	return max;
}

int getMin(int* numbers, int array_size) {
	int min = *numbers;
	for (int i = 1; i < array_size; i++)
		if (*(numbers + i) < min)
			min = *(numbers + i);
	return min;
}