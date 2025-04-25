#include <iostream>

using namespace std;

int minimumLength(int a[], int n, int target)
{
    int i = 0, j = 1, length = 999999;
    int val = a[0];
    while (i < n)
    {
        if (val <= target)
        {
            val += a[j];
            j++;
        }
        else
        {
            if (j - i < length)
            {
                length = j - i;
            }
            val -= a[i];
            i++;
        }
    }
    
    while (i < n && val > target){
        val -= a[i];
        i++;
    }
    
    if (j - i + 1 < length){
        length = j - i + 1;
    }
    return length;
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
    int target = 0;
    cin >> target;

    cout << minimumLength(a, n, target);
    return 0;
}