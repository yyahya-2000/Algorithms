#include <iostream>
#include <fstream>

using namespace std;

class ReadWriter
{
private:

	std::fstream fin;
	std::fstream fout;

public:

	~ReadWriter()
	{
		fin.close();
		fout.close();
	}

	ReadWriter()
	{
		fin.open("input.txt", std::ios::in);
		fout.open("output.txt", std::ios::out);
	}

	int readInt()
	{
		if (!fin.is_open())
			throw std::ios_base::failure("file not open");

		int n = 0;
		fin >> n;
		return n;
	}

	//This method only fill array. You should create it before call this method.
	void readArray(int* arr, int length)
	{
		if (!fin.is_open())
			throw std::ios_base::failure("file not open");

		for (int i = 0; i < length; i++)
			fin >> arr[i];
	}

	void writeInt(int n)
	{
		if (!fout.is_open())
			throw std::ios_base::failure("file not open");
		fout << n << "\n";
	}

	void writeArray(int* arr, int n)
	{
		if (!fout.is_open())
			throw std::ios_base::failure("file not open");
		for (int i = 0; i < n; i++)
			fout << arr[i] << " ";
	}
};

int recNum = 0;
int lomuto(int* nums, int left, int right) {
	recNum++;
	int pivot = *(nums + right);
	int i = left;
	for (int j = left; j < right; j++)
		if (*(nums + j) <= pivot) {
			swap(*(nums + i), *(nums + j));
			i++;
		}
	swap(*(nums + i), *(nums + right));
	return i;
}

void quickSort(int* nums, int left, int right) {

	if (left < right) {
		int pivot = lomuto(nums, left, right);
		if (pivot - 1 > left)
			quickSort(nums, left, pivot - 1);
		if (pivot + 1 < right)
			quickSort(nums, pivot + 1, right);
	}
}



int main()
{
	//Объект для работы с файлами
	ReadWriter rw;

	int* nums = nullptr;
	int n;

	//Ввод из файла
	n = rw.readInt();

	nums = new int[n];
	rw.readArray(nums, n);

	//Запуск сортировки, ответ в том же массиве (brr)
	quickSort(nums, 0, n - 1);

	rw.writeInt(--recNum);

	//Запись в файл
	rw.writeArray(nums, n);

	//освобождаем память
	delete[] nums;

	return 0;
}