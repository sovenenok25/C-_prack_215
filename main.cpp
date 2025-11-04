#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int low, int high, int pivot) {
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int pivot;
    cin >> pivot;
    if (n==0){
        cout<<"0"<<endl;
        cout<<"0"<<endl;
    }
    int partitionIndex = partition(arr, 0, n - 1, pivot);

    int countLessThanX = partitionIndex + 1;
    int countGreaterThanX = n - countLessThanX;

    cout << countGreaterThanX << endl;
    cout << countLessThanX << endl;


    return 0;
}

