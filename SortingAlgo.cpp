#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Utility function to print an array
void printArray(vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// 1. Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// 2. Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// 3. Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// 5. Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 7. Shell Sort
void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 8. Counting Sort
void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    for (int num : arr) count[num]++;
    int idx = 0;
    for (int i = 0; i <= maxVal; i++)
        while (count[i]--) arr[idx++] = i;
}

// 9. Radix Sort
void countingSortRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);
    for (int num : arr) count[(num / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortRadix(arr, exp);
}

// 10. Bucket Sort
void bucketSort(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> buckets(n);
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int num : arr) {
        int idx = (num * n) / (maxVal + 1);
        buckets[idx].push_back(num);
    }
    for (auto& bucket : buckets) sort(bucket.begin(), bucket.end());

    int idx = 0;
    for (auto& bucket : buckets)
        for (int num : bucket)
            arr[idx++] = num;
}

// 11. Tim Sort (using built-in sort)
void timSort(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}

// Main function to test sorting algorithms
int main() {
    vector<int> originalArr = {64, 34, 25, 12, 22, 11, 90}; // Keep the original array

    vector<int> arr; // Declare an array to copy originalArr into

    // 1. Bubble Sort
    arr = originalArr; 
    bubbleSort(arr);
    cout << "Bubble Sort: ";
    printArray(arr);

    // 2. Selection Sort
    arr = originalArr; 
    selectionSort(arr);
    cout << "Selection Sort: ";
    printArray(arr);

    // 3. Insertion Sort
    arr = originalArr; 
    insertionSort(arr);
    cout << "Insertion Sort: ";
    printArray(arr);

    // 4. Merge Sort
    arr = originalArr; 
    mergeSort(arr, 0, arr.size() - 1);
    cout << "Merge Sort: ";
    printArray(arr);

    // 5. Quick Sort
    arr = originalArr; 
    quickSort(arr, 0, arr.size() - 1);
    cout << "Quick Sort: ";
    printArray(arr);

    // 6. Heap Sort
    arr = originalArr; 
    heapSort(arr);
    cout << "Heap Sort: ";
    printArray(arr);

    // 7. Shell Sort
    arr = originalArr; 
    shellSort(arr);
    cout << "Shell Sort: ";
    printArray(arr);

    // 8. Counting Sort
    arr = originalArr; 
    countingSort(arr);
    cout << "Counting Sort: ";
    printArray(arr);

    // 9. Radix Sort
    arr = originalArr; 
    radixSort(arr);
    cout << "Radix Sort: ";
    printArray(arr);

    // 10. Bucket Sort
    arr = originalArr; 
    bucketSort(arr);
    cout << "Bucket Sort: ";
    printArray(arr);

    // 11. Tim Sort
    arr = originalArr; 
    timSort(arr);
    cout << "Tim Sort: ";
    printArray(arr);

    return 0;
}
