#include "headers.hpp"
template <class T>

void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

// Hàm tính thời gian thuật toán chạy (tham khảo ChatGPT)
template <typename Func>

long long measureTime(Func sortFunction) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(); // chạy thuật toán sắp xếp
    auto end = std::chrono::high_resolution_clock::now();
	// Đơn vị đo là micro giây
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count();
}

void Selection_sort(int a[], int n, long long& count){
	for (int i = 0; i < n - 1; i++){
		int minIdx = i;
		for (int j = i + 1; j < n; j++){
			count++;
			if (a[j] < a[minIdx]){
				minIdx = j;
			}
		}
		HoanVi(a[i], a[minIdx]);
	}
}

void Insertion_sort(int a[], int n, long long& count){
	for (int i = 1; i < n; i++){
		int j = i - 1, key = a[i];
		while (j >= 0){
			count++;
			if (a[j] > key){
				a[j + 1] = a[j];
				j--;
			} else {
				break;
			}
		}		
		a[j + 1] = key;
	}
}

void Bubble_sort(int a[], int n, long long& count){
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			count++;
			if (a[j] > a[j + 1]){
				HoanVi(a[j], a[j + 1]);
			}
		}
	}
}

void Shaker_sort(int a[], int n, long long& count){
    int start = 0, end = n - 1;
    bool swapped = false;

    while (start < end) {
        swapped = false;

        for (int i = start; i < end; i++) {
            if (a[i] > a[i + 1]) {
                count++;
                HoanVi(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        end--;

        swapped = false;

        for (int i = end; i > start; i--) {
			count++;
            if (a[i] < a[i - 1]) {
                HoanVi(a[i], a[i - 1]);
                swapped = true;
            }
        }

        start++;
    }
}

void Shell_sort(int a[], int n, long long& count){
	for (int gap = n / 2; gap > 0; gap /= 2){
		for (int i = gap; i < n; i++){
			int key = a[i], j = i;
			while (j >= gap) {
                count++;
                if (a[j - gap] > key) {
                    a[j] = a[j - gap];
                    j -= gap;
                } else {
                    break;
                }
            }
			a[j] = key;
		}
	}
}

void Heapify(int a[], int n, int i, long long& count){
	int maxPos = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n){
		count++;
		if (a[left] > a[maxPos]){
			maxPos = left;
		}
	}

	if (right < n){
		count++;
		if (a[right] > a[maxPos]){
			maxPos = right;
		}
	}

	if (maxPos != i){
		HoanVi(a[i], a[maxPos]);
		Heapify(a, n, maxPos, count);
	}
}

void Heap_sort(int a[], int n, long long& count){
	for (int i = n / 2 - 1; i >= 0; i--){
		Heapify(a, n, i, count);
	}

	for (int i = n - 1; i >= 0; i--){
		HoanVi(a[0], a[i]);
		Heapify(a, i, 0, count);
	}
}

void Merge(int a[], int left, int mid, int right, long long& count){
	int n1 = mid - left + 1, n2 = right - mid;
	int l[n1], r[n2];

	for (int i = 0; i < n1; i++){
		l[i] = a[left + i];
	}

	for (int i = 0; i < n2; i++){
		r[i] = a[mid + i + 1];
	}

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2){
		count++;
		if (l[i] <= r[j]){
			a[k++] = l[i++];
		}else{
			a[k++] = r[j++];
		}
	}

	for (; i < n1; i++){
		a[k++] = l[i];
	}

	for (; j < n2; j++){
		a[k++] = r[j];
	}
}

void Merge_sort(int a[], int left, int right, long long& count){
	if (left < right){
		int mid = left + (right - left) / 2;

		Merge_sort(a, left, mid, count);
		Merge_sort(a, mid + 1, right, count);
		Merge(a, left, mid, right, count);
	}
}

int medianOfThree(int a[], int low, int high, long long& count) {
    int mid = (low + high) / 2;
	count++;
    if (a[low] > a[mid]) HoanVi(a[low], a[mid]);

	count++;
    if (a[low] > a[high]) HoanVi(a[low], a[high]);

	count++;
    if (a[mid] > a[high]) HoanVi(a[mid], a[high]);

    return mid;
}

int hoarePartition_with_medianOfThree(int a[], int low, int high, long long& count) {
    int mid = medianOfThree(a, low, high, count);
    int pivot = a[mid];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
			i++; 
		//  count++; 
		} while (a[i] < pivot);
        do {
			j--;
			count++;
		} while (a[j] > pivot);

        if (i >= j){
			return j;
		}
        HoanVi(a[i], a[j]);
    }
}

void Quick_sort_Hoare_with_medianOfThree(int a[], int low, int high, long long& count){
	if (low < high){
		int pivot = hoarePartition_with_medianOfThree(a, low, high, count);
		Quick_sort_Hoare_with_medianOfThree(a, low, pivot, count);
		Quick_sort_Hoare_with_medianOfThree(a, pivot + 1, high, count);
	}
}

int lomutoPartition_with_medianOfThree(int a[], int low, int high, long long& count){
    int mid = medianOfThree(a, low, high, count);
    int pivot = a[mid];
	int i = low - 1;

	for (int j = low; j < high; j++){
		count++;
		if (a[j] < pivot){
			i++;
			HoanVi(a[i], a[j]);
		}
	}

	HoanVi(a[i + 1], a[high]);
	return i + 1;
}

void Quick_sort_Lomuto_with_medianOfThree(int a[], int low, int high, long long& count){
	if (low < high){
		int pivot = lomutoPartition_with_medianOfThree(a, low, high, count);
		Quick_sort_Lomuto_with_medianOfThree(a, low, pivot - 1, count);
		Quick_sort_Lomuto_with_medianOfThree(a, pivot + 1, high, count);
	}
}

int hoarePartition_without_medianOfThree(int a[], int low, int high, long long& count) {
    int pivot = a[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
            count++;
        } while (a[i] < pivot);

        do {
            j--;
            count++;
        } while (a[j] > pivot);

        if (i >= j)
            return j;

        HoanVi(a[i], a[j]);
    }
}

void Quick_sort_Hoare_without_medianOfThree(int a[], int low, int high, long long& count) {
    if (low < high) {
        int pivot = hoarePartition_without_medianOfThree(a, low, high, count);
        Quick_sort_Hoare_without_medianOfThree(a, low, pivot, count);
        Quick_sort_Hoare_without_medianOfThree(a, pivot + 1, high, count);
    }
}

int lomutoPartition_without_medianOfThree(int a[], int low, int high, long long& count) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        count++;
        if (a[j] < pivot) {
            i++;
            HoanVi(a[i], a[j]);
        }
    }

    HoanVi(a[i + 1], a[high]);
    return i + 1;
}

void Quick_sort_Lomuto_without_medianOfThree(int a[], int low, int high, long long& count) {
    if (low < high) {
        int pivot = lomutoPartition_without_medianOfThree(a, low, high, count);
        Quick_sort_Lomuto_without_medianOfThree(a, low, pivot - 1, count);
        Quick_sort_Lomuto_without_medianOfThree(a, pivot + 1, high, count);
    }
}

int getMax(int a[], int n, long long& count){
	int max = a[0];
	for (int i = 1; i < n; i++){
		count++;
		if (a[i] > max){
			max = a[i];
		}
	}

	return max;
}

void Counting_sort(int a[], int n, long long& count) {
    int maxVal = getMax(a, n, count);
    vector<int> p(maxVal + 1, 0);

    for (int i = 0; i < n; i++) {
        p[a[i]]++;
    }

    for (int i = 1; i <= maxVal; i++) {
        p[i] += p[i - 1];
    }

    vector<int> temp(n);
    for (int i = n - 1; i >= 0; i--) {
        temp[p[a[i]] - 1] = a[i];
        p[a[i]]--;
    }

    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }
}

void Radix_sort(int a[], int n, long long& count) {
    if (n <= 1) {
        return;
    }

    int max = a[0];
    for (int i = 1; i < n; i++) {
        count++;
        if (a[i] > max) {
            max = a[i];
        }
    }

    int exp = 1;
    while (max / exp >= 10) {
        exp *= 10;
    }

    vector<int> bucket[10];
    while (exp > 0) {
        for (int i = 0; i < n; i++) {
            int digit = (a[i] / exp) % 10;
            bucket[digit].push_back(a[i]);
        }

        int temp = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < bucket[i].size(); j++) {
                a[temp++] = bucket[i][j];
            }
            bucket[i].clear();
        }

        exp /= 10;
    }
}

int getMaxIndex(int a[], int n, long long& count){
	int maxIdx = 0;
	for (int i = 1; i < n; i++){
		count++;
		if (a[i] > a[maxIdx]){
			maxIdx = i;
		}
	}

	return maxIdx;
}

int getMin(int a[], int n, long long& count){
	int min = a[0];
	for (int i = 1; i < n; i++){
		count++;
		if (a[i] < min){
			min = a[i];
		}
	}

	return min;
}

void Flash_sort(int a[], int n, long long& count) {
    if (n <= 1) return;

    int minVal = getMin(a, n, count);
    int maxIdx = getMaxIndex(a, n, count);
    int maxVal = a[maxIdx];

    if (minVal == maxVal) return;

    int m = int(0.43 * n);
    vector<int> L(m, 0);

    double c = (double)(m - 1) / (maxVal - minVal);

    for (int i = 0; i < n; i++) {
        int k = int(c * (a[i] - minVal));
        L[k]++;
    }

    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    HoanVi(a[maxIdx], a[0]);

    int move = 0;
    int j = 0, k = m - 1;
    while (move < n - 1) {
        while (j > L[k] - 1) {
            j++;
            k = int(c * (a[j] - minVal));
        }

        int evicted = a[j];
        while (j != L[k]) {
            k = int(c * (evicted - minVal));
            int index = --L[k];
            HoanVi(evicted, a[index]);
            move++;
        }
    }

    Insertion_sort(a, n, count);
}