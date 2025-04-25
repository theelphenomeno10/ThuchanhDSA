#include <iostream>

using namespace std;

int getMaximum(int a[], int n)
{
    int maxval = 0;
    for (int i = 0; i < n; i++)
    {
        if (maxval < a[i])
        {
            maxval = a[i];
        }
    }
    return maxval;
}

bool checkWeight(int a[], int n, int maxweight, int d)
{
    int tempD = 1, sumTemp = 0;
    for (int i = 0; i < n; i++)
    {
        if (sumTemp + a[i] > maxweight)
        {
            tempD++;
            sumTemp = a[i];
        }
        else
        {
            sumTemp += a[i];
        }
        if (tempD > d)
        {
            return false;
        }
    }
    return true;
}

int MinimumCapacity(int a[], int n, int d)
{
    int tempweight = getMaximum(a, n);
    while (!checkWeight(a, n, tempweight, d))
    {
        tempweight++;
    }
    return tempweight;
}

int main()
{
    int n = 0;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int day = 0;
    cin >> day;
    cout << MinimumCapacity(a, n, day);
}