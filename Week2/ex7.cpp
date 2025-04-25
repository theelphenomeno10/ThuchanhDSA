#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> Triplets_Sum_Equal_Zero(int a[], int n){
    sort(a, a + n);
    vector<vector<int>> result;

    for (int i = 0; i < n - 2; i++){
        if (i > 0 && a[i] == a[i + 1]){
            ++i;
        }

        int left = i + 1, right = n - 1;
        while (left < right){
            if (a[i] + a[left] + a[right] == 0){
                result.push_back({a[i], a[left], a[right]});
                left++;
                right--;

                while (left < right && a[left] == a[left - 1]){
                    left++;
                }

                while (right > left && a[right] == a[right - 1]){
                    right--;
                }
            }else if (a[i] + a[left] + a[right] < 0){
                left++;
            }else{
                right--;
            }
        }
    }
    return result;
}

int main(){
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> result = Triplets_Sum_Equal_Zero(a, n);

    cout << "[";
    for (int i = 0; i < result.size(); i++){
        cout << "[";
        for (int j = 0; j < 3; j++){
            cout << result[i][j];
            if (j != 2){
                cout << ",";
            }else{
                cout << "]";
            }
        }
    }
    return 0;
}