#include <iostream>

int FindMinNumberInRotatedSortedArray(int a[], int left, int right)
{
    if (left >= right)
    {
        return a[left];
    }

    int mid = left + (right - left) / 2;
    if (a[mid] < a[right])
    {
        return FindMinNumberInRotatedSortedArray(a, left, mid);
    }
    else
    {
        return FindMinNumberInRotatedSortedArray(a, mid, right);
    }
}

int main()
{
    int n;
    std::cin >> n;
    int *ptr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> ptr[i];
    }
    std::cout << FindMinNumberInRotatedSortedArray(ptr, 0, n - 1);
    return 0;
}