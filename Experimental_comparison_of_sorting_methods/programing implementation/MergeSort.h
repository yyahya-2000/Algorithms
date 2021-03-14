
class MergeSort
{
private:
	void merge(int* array, int l, int m, int r) {
		int i, j, k;
		//size of left and right sub-arrays
		const int nl = m - l + 1;
		const int nr = r - m;
		int* larr = new int[nl];
		int* rarr = new int[nr];
		//fill left and right sub-arrays
		for (i = 0; i < nl; i++)
			larr[i] = array[l + i];
		for (j = 0; j < nr; j++)
			rarr[j] = array[m + 1 + j];
		i = 0; j = 0; k = l;
		//marge temp arrays to real array
		while (i < nl && j < nr) {
			if (larr[i] <= rarr[j]) {
				array[k] = larr[i];
				i++;
			}
			else {
				array[k] = rarr[j];
				j++;
			}
			k++;
		}
		while (i < nl) {       //extra element in left array
			array[k] = larr[i];
			i++; k++;
		}
		while (j < nr) {     //extra element in right array
			array[k] = rarr[j];
			j++; k++;
		}
	}

	void originalMergeSort(int* array, int l, int r) {
		int m;
		if (l < r) {
			m = l + (r - l) / 2;
			// Sort first and second arrays
			originalMergeSort(array, l, m);
			originalMergeSort(array, m + 1, r);
			merge(array, l, m, r);
		}
	}
public:
	void mergeSort(int* arr, int arraySize) {
		originalMergeSort(arr, 0, arraySize - 1);
	}
};

