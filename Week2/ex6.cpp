#include <iostream>

using namespace std;

bool Exist_Two_Sum(int a[], int n, int left, int right, int target){
    if (left > right){
        return false;
    }

    if (a[left] + a[right] > target){
        return Exist_Two_Sum(a, n, left, right - 1, target);
    }else if (a[left] + a[right] < target){
        return Exist_Two_Sum(a, n, left + 1, n - 1, target);
    }else{
        return true;
    }
}

int main(){
    int n;
    cin >> n;

    int *a = new int[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    int target;
    cin >> target;

    if (Exist_Two_Sum(a, n, 0, n - 1, target)){
        cout << "YES";
    }else{
        cout << "NO";
    }

    return 0;
}