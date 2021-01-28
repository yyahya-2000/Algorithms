#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//function to get the min value between all values in "numbers"
int getMax(int* numbers, int array_size);

//function to get the max value between all values in "numbers"
int getMin(int* numbers, int array_size);

// Функция сортировки подсчетом
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

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
	//Объект для работы с файлами
	ReadWriter rw;

	int* brr = nullptr;
	int n;

	//Ввод из файла
	n = rw.readInt();

	brr = new int[n];
	rw.readArray(brr, n);

	//Запуск сортировки, ответ в том же массиве (brr)
	countingSort(brr, n);

	//Запись в файл
	rw.writeArray(brr, n);

	//освобождаем память
	delete[] brr;

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
