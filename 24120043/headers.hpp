#ifndef REPORT_ON_SORTING_ALGORITHM
#define REPORT_ON_SORTING_ALGORITHM

#include <iostream>
#include <fstream>
#include <cmath>
// Dùng để đo thời gian
#include <time.h>
#include <vector>
// Dùng để đo thời gian
#include <chrono>
// Dùng để đọc command line
#include <getopt.h>
// Dùng để đọc chuỗi trong command line
#include <string>

using namespace std::chrono;
using namespace std;

// Các hàm có sử dụng
// Các hàm đề cho
template <class T>
void HoanVi(T &a, T &b);
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);

// Hàm đo thời gian này có sử dụng ChatGPT
template <typename Func>
long long measureTime(Func sortFunction);

// Các hàm sắp xếp
void Selection_sort(int a[], int n, long long& count);

void Insertion_sort(int a[], int n, long long& count);

void Bubble_sort(int a[], int n, long long& count);

void Shaker_sort(int a[], int n, long long& count);

void Shell_sort(int a[], int n, long long& count);

void Heapify(int a[], int n, int i, long long& count);
void Heap_sort(int a[], int n, long long& count);

void Merge(int a[], int left, int mid, int right, long long& count);
void Merge_sort(int a[], int left, int right, long long& count);

// Hàm chọn trung vị để cho Quick sort nhanh hơn trong trường hợp xấu
int medianOfThree(int a[], int low, int high, long long& count);

// Hàm chọn pivot cho Quick sort sử dụng phân hoạch Hoare tránh trường hợp xấu
// Phân hoạch Hoare nhanh hơn phân hoạch Lomuto được học trên trường
int hoarePartition_with_medianOfThree(int a[], int low, int high, long long& count);
void Quick_sort_Hoare_with_medianOfThree(int a[], int low, int high, long long& count);

// Hàm chọn pivot cho Quick sort sử dụng phân hoạch Lomuto và chọn trung vị tránh trường hợp xấu
int lomutoPartition_with_medianOfThree(int a[], int low, int high, long long& count);
void Quick_sort_Lomuto_with_medianOfThree(int a[], int low, int high, long long& count);

// Quick sort không dùng cách chọn trung vị
    // Sử dụng phân hoạch Hoare
int hoarePartition_without_medianOfThree(int a[], int low, int high, long long& count);
void Quick_sort_Hoare_without_medianOfThree(int a[], int low, int high, long long& count);
    // Sử dụng phân hoạch Lomuto
int lomutoPartition_without_medianOfThree(int a[], int low, int high, long long& count);
void Quick_sort_Lomuto_without_medianOfThree(int a[], int low, int high, long long& count);

// Hàm lấy số lớn nhất cho các thuật toán sắp xếp phân loại
int getMax(int a[], int n, long long& count);

void Counting_sort(int a[], int n, long long& count);

void Radix_sort(int a[], int n, long long& count);

// Hàm lấy vị trí số lớn nhất cho Flash sort
int getMaxIndex(int a[], int n, long long& count);

// Hàm lấy số nhỏ nhất cho Flash sort
int getMin(int a[], int n, long long& count);

// Hàm Flash sort tham khảo ChatGPT và tự thực hiện lại
void Flash_sort(int a[], int n, long long& count);

#endif