#include <iostream>
#include <fstream>

using namespace std;


void quickSort(int* nums, int left, int right) {
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
			swap(*(nums + i), *(nums + j));
			i++;
			j--;
		}
		if (!(i <= j))
			break;
	}
	if (left < j)
		quickSort(nums, left, j);
	if (right > i)
		quickSort(nums, i, right);
}

// increment i or j or k or return false to signal about finishing search process
bool doStep(const int* minArr, const int* mediumArr, const int* maxArr, const int* nMin,
	const int* nMed, int* i, int* j, int* k) {
	if (*i + 1 < *nMin && (minArr[*i + 1] < mediumArr[*j] || minArr[*i + 1] < maxArr[*k]))
		(*i)++;
	else if (*j + 1 < *nMed && mediumArr[*j + 1] < maxArr[*k])
		(*j)++;
	else if (*i + 1 < *nMin && *j + 1 < *nMed) {
		if (minArr[*i + 1] < mediumArr[*j + 1])
			(*i)++;
		else
			(*j)++;
	}
	else if (*i + 1 == *nMin && *j + 1 == *nMed)
		return false;
	else if (*i + 1 == *nMin)
		(*j)++;
	else if (*j + 1 == *nMed)
		(*i)++;
	return true;
}

int* arrCurrentNums = new int[3];

bool moveController(const int* r, const int* g, const int* b, const int* nr,
	const int* ng, const int* nb, int* i, int* j, int* k) {

	arrCurrentNums[0] = r[*i];
	arrCurrentNums[1] = g[*j];
	arrCurrentNums[2] = b[*k];

	/*
	* min -> arrCurrentNums[0]
	* med -> arrCurrentNums[1]
	* max -> arrCurrentNums[2]
	*/
	quickSort(arrCurrentNums, 0, 2);

	//if r[*i] < g[*j] && r[*i] < b[*k]
	if (arrCurrentNums[0] == r[*i]) {
		if (arrCurrentNums[1] == g[*j])
			// r[*i] < g[*j] < b[*k]
			return doStep(r, g, b, nr, ng, i, j, k);
		else
			return doStep(r, b, g, nr, nb, i, k, j);
	}
	//if g[*j] < r[*i] && g[*j] < b[*k]
	else if (arrCurrentNums[0] == g[*j]) {
		if (arrCurrentNums[1] == r[*i])
			return doStep(g, r, b, ng, nr, j, i, k);
		else
			return doStep(g, b, r, ng, nb, j, k, i);
	}
	//if b[*k] < r[*i] && b[*k] < g[*j]
	else {
		if (arrCurrentNums[1] == r[*i])
			return doStep(b, r, g, nb, nr, k, i, j);
		else
			return doStep(b, g, r, nb, ng, k, j, i);
	}
}

// Необходимо вернуть вектор ans, который содержит три элемента:
// ans[0] - вес найденного самоцвета красного цвета
// ans[1] - вес найденного самоцвета зеленого цвета
// ans[2] - вес найденного самоцвета синего цвета
int* solve(int nr, int ng, int nb, int* r, int* g, int* b)
{
	int* ans = new int[3];

	quickSort(r, 0, nr - 1);
	quickSort(g, 0, ng - 1);
	quickSort(b, 0, nb - 1);
	int64_t minFunValue = INT64_MAX;
	int64_t currentfunValue;
	int curMinVal;
	int i = 0, j = 0, k = 0;
	while (i < nr && j < ng && k < nb)
	{
		currentfunValue = (static_cast<long long>(*(r + i)) - *(g + j)) * (static_cast<long long>(*(r + i)) - *(g + j)) +
			(static_cast<long long>(*(g + j)) - *(b + k)) * (static_cast<long long>(*(g + j)) - *(b + k)) +
			(static_cast<long long>(*(r + i)) - *(b + k)) * (static_cast<long long>(*(r + i)) - *(b + k));

		if (currentfunValue < minFunValue) {
			ans[0] = r[i];
			ans[1] = g[j];
			ans[2] = b[k];
			minFunValue = currentfunValue;
		}

		if (minFunValue == 0)
			return ans;

		if (!moveController(r, g, b, &nr, &ng, &nb, &i, &j, &k))
			break;
	}
	return ans;
}

int main() {
	fstream fin;
	fstream fout;
	fin.open("input.txt", ios::in);
	fout.open("output.txt", ios::out);

	if (fin.is_open()) {
		int t;
		fin >> t;
		while (t--) {
			int nr, ng, nb;
			fin >> nr >> ng >> nb;

			int* r = new int[nr];
			int* g = new int[ng];
			int* b = new int[nb];
			for (int i = 0; i < nr; ++i)
				fin >> r[i];
			for (int i = 0; i < ng; ++i)
				fin >> g[i];
			for (int i = 0; i < nb; ++i)
				fin >> b[i];

			int* ans = solve(nr, ng, nb, r, g, b);

			fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;

			delete[] r;
			delete[] g;
			delete[] b;
			delete[] ans;
		}
	}
	fin.close();
	fout.close();
	return 0;
}


