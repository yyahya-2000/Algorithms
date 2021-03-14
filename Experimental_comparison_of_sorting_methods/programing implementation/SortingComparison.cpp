/*
АиСД-2, 2021, задание 5
ФИГ: Яхя Янал | БПИ197
Среда разработки: Visual Studio 2019
всё сделано
*/
#include"BinaryInsertsSort.h"
#include"CountingSort.h"
#include"Heapsort.h"
#include"MergeSort.h"
#include"QuickSortMiddlePivot.h"
#include"RadixSortByBase_256.h"
#include"SelectionSort.h"
#include"SimpleInsertSort.h"
#include"ArrayGenerator.h"
#include "ReaderWriter.h"
#include <functional>
#include <chrono>

using namespace std;
using namespace std::placeholders;

ArrayGenerator arrayGen;
BinaryInsertsSort binaryInserts;
CountingSort counting;
Heapsort heap;
MyQuickSort quick;
RadixSort radix;
SelectionSort selection;
SimpleInsertsSort simpleInserts;
MergeSort merge_;

bool isSorted(int* arr, int n) {
	bool sorted = true;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			sorted = false;
			break;
		}
	}
	return sorted;
}

//method for test  all sort algorithms on data from input file
void TestSortAlgorithms() {
	ReadWriter rw;
	int* input = nullptr;
	int* output = nullptr;
	int n = rw.readInt();
	input = new int[n];
	output = new int[n];
	rw.readArray(input, n);
	rw.writeString("Selection sort:");
	copy(input, input + n, output);
	selection.selectionSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nSimple inserts sort:");
	copy(input, input + n, output);
	simpleInserts.simpleInsertsSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nBinary inserts sort:");
	copy(input, input + n, output);
	binaryInserts.binaryInsertsSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nCounting sort:");
	copy(input, input + n, output);
	counting.countingSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nRadix sort:");
	copy(input, input + n, output);
	radix.radixSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nMerge sort:");
	copy(input, input + n, output);
	merge_.mergeSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nQuicksort:");
	copy(input, input + n, output);
	quick.quickSort(output, n);
	rw.writeArray(output, n);
	rw.writeString("\nHeapsort:");
	copy(input, input + n, output);
	heap.heapSort(output, n);
	rw.writeArray(output, n);
	delete[] input;
	delete[] output;
}

int main()
{
	// Create an output filestream object
	ofstream myFile("result.csv");

	int* A = nullptr;
	int* B = nullptr;
	long long sum;
	int count = 0;

	/* create vector of all sort metods*/
	vector<function<void(int*, int)>> functions;
	functions.emplace_back(bind(&SelectionSort::selectionSort, &selection, _1, _2));
	functions.emplace_back(bind(&SimpleInsertsSort::simpleInsertsSort, &simpleInserts, _1, _2));
	functions.emplace_back(bind(&BinaryInsertsSort::binaryInsertsSort, &binaryInserts, _1, _2));
	functions.emplace_back(bind(&CountingSort::countingSort, &counting, _1, _2));
	functions.emplace_back(bind(&RadixSort::radixSort, &radix, _1, _2));
	functions.emplace_back(bind(&MergeSort::mergeSort, &merge_, _1, _2));
	functions.emplace_back(bind(&MyQuickSort::quickSort, &quick, _1, _2));
	functions.emplace_back(bind(&Heapsort::heapSort, &heap, _1, _2));

	int Nb = 50, Ne = 300, Nd = 50;
	int rem;
	for (int l = 0; l < 2; l++)
	{
		// sorting algorithms
		for (const auto& fn : functions)
		{
			//array types
			for (int j = 1; j < 5; j++)
			{
				A = new int[Ne];
				arrayGen.generateArray(A, Ne, j);
				for (int k = Nb; k <= Ne; k += Nd)
				{
					B = new int[k];
					sum = 0;
					for (int i = 0; i < 50; i++)
					{
						copy(A, A + k, B);
						auto start = chrono::high_resolution_clock::now();
						fn(B, k);
						auto elapsed = chrono::high_resolution_clock::now() - start;
						long long nanoseconds = chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
						sum += nanoseconds;
						if (!isSorted(B, k)) {
							exit(-1);
						}
					}
					/*just for formating*/
					myFile << /*time avg*/(sum / 50) << ";";
					rem = l == 0 ? 6 : 5;
					if (++count % rem == 0)
						myFile << endl;

					delete[] B;
				}

			}
			delete[] A;
		}
		myFile << "\n\n\n";
		Nb = 100;
		Ne = 4100;
		Nd = 1000;
		count = 0;
	}

	TestSortAlgorithms();

	myFile.close();
}