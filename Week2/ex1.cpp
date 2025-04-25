#include <iostream>

int LinearSearch(int a[], int n, int target)
{
    if (n < 0)
    {
        return -1;
    }
    if (a[n - 1] == target)
    {
        return n - 1;
    }
    return LinearSearch(a, n - 1, target);
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
    int target;
    std::cin >> target;
    std::cout << LinearSearch(ptr, n, target);
    return 0;
}