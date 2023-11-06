#include <bits/stdc++.h>
using namespace std;

int getPivotDeterministic(vector<int> &arr, int low, int high){
    int lowerIdx = low;
    int pivot = arr[high];
    
    for(int i = low; i < high; i++){
        if(arr[i] <= pivot){
            swap(arr[i], arr[lowerIdx]);
            lowerIdx++;
        }
    }    
    
    swap(arr[lowerIdx], arr[high]);
    return lowerIdx;
}

void quickSortDeterministic(vector<int> &arr, int low, int high){
    if(low < high){
        int pivot = getPivotDeterministic(arr, low, high);
        quickSortDeterministic(arr, low, pivot - 1);
        quickSortDeterministic(arr, pivot + 1, high);
    }
}

int getPivotRandom(vector<int> &arr, int low, int high){
    srand(time(NULL));
    int pivotIdx = low + (rand() % (high - low));

    int lowerIdx = low;
    int pivot = arr[pivotIdx];
    
    swap(arr[high], arr[pivotIdx]);
    
    for(int i = low; i < high; i++){
        if(arr[i] <= pivot){
            swap(arr[i], arr[lowerIdx]);
            lowerIdx++;
        }
    }    
    
    swap(arr[lowerIdx], arr[high]);
    return lowerIdx;
}

void quickSortRandom(vector<int> &arr, int low, int high){
    if(low < high){
        int pivot = getPivotRandom(arr, low, high);
        quickSortRandom(arr, low, pivot - 1);
        quickSortRandom(arr, pivot + 1, high);
    }
}

int main(){
    vector<int> arr1 = {1, 3, 2, 9, 1, 2, 6, 3, 5, 2};
    vector<int> arr2 = {1, 3, 2, 9, 1, 2, 6, 3, 5, 2};
    
    quickSortDeterministic(arr1, 0, arr1.size() - 1);
    quickSortRandom(arr2, 0, arr2.size() - 1);
    
    for(auto num: arr1) cout << num << " ";
    cout << endl;
    
    for(auto num: arr2) cout << num << " ";
    cout << endl;
    
    return 0;
}
