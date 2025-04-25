#include <iostream>

using namespace std;

int LinearSearchWithSentinel(int a[], int n, int target, int temp)
{
    if (n < 0)
    {
        return -1;
    }
    if (target == temp)
    {
        return 0;
    }
    a[0] = target;
    if (a[n - 1] == target)
    {
        return n - 1;
    }
    return LinearSearchWithSentinel(a, n - 1, target, temp);
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
    std::cout << LinearSearchWithSentinel(ptr, n, target, ptr[0]);
    return 0;
}