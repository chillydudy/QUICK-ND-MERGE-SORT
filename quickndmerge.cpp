#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;


void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* LeftArr = new int[n1];
    int* RightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        LeftArr[i] = arr[left + i];
        
    for (int j = 0; j < n2; j++)
        RightArr[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (LeftArr[i] <= RightArr[j]) {
            arr[k] = LeftArr[i];
            i++;
        } else {
            arr[k] = RightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = LeftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = RightArr[j];
        j++;
        k++;
    }

    delete[] LeftArr;
    delete[] RightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


int partition(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]);
    
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void runTest(int n, string type) {
    int* arr1 = new int[n];
    int* arr2 = new int[n];

    for (int i = 0; i < n; i++) {
        if (type == "Random") {
            arr1[i] = rand() % 10000;
        } else if (type == "Sorted") {
            arr1[i] = i;
        } else if (type == "Reverse") {
            arr1[i] = n - i;
        }
        arr2[i] = arr1[i];
    }

    cout << "Type: " << type << " | Size: " << n << endl;

    clock_t start = clock();
    mergeSort(arr1, 0, n - 1);
    clock_t end = clock();
    
    cout << "  Merge Sort: " << double(end - start) / CLOCKS_PER_SEC << " s" << endl;

    start = clock();
    quickSort(arr2, 0, n - 1);
    end = clock();
    
    cout << "  Quick Sort: " << double(end - start) / CLOCKS_PER_SEC << " s" << endl;
    cout << "---------------------------------" << endl;

    delete[] arr1;
    delete[] arr2;
}

int main() {
    srand(time(0));
    
    cout << "=== ALGORITHM PERFORMANCE ANALYSIS ===" << endl;

    runTest(1000, "Random");
    
    runTest(10000, "Random");
    runTest(10000, "Sorted");
    runTest(10000, "Reverse");

    runTest(50000, "Random");

    return 0;
}
