#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for Sparse Matrix Representation
struct SparseElement {
    int row, col, value;
};

// Function to convert a matrix to sparse representation
vector<SparseElement> convertToSparse(vector<vector<int>>& matrix) {
    vector<SparseElement> sparse;
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse.push_back({i, j, matrix[i][j]});
            }
        }
    }
    return sparse;
}

// Function to display sparse matrix representation
void displaySparseMatrix(vector<SparseElement>& sparse) {
    cout << "\nSparse Matrix Representation (Row, Column, Value):\n";
    for (const auto& elem : sparse) {
        cout << elem.row << " " << elem.col << " " << elem.value << endl;
    }
}

// Function to perform Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high]; 
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to perform Binary Search
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // Element not found
}

// Function to compute Prefix Sum
vector<int> prefixSum(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    return prefix;
}

// Main function
int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Sorting
    quickSort(arr, 0, n - 1);
    cout << "Sorted Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    // Searching
    int target;
    cout << "Enter the element to search: ";
    cin >> target;
    int index = binarySearch(arr, target);
    if (index != -1) cout << "Element " << target << " found at index: " << index << endl;
    else cout << "Element " << target << " not found\n";

    // Prefix Sum Calculation
    vector<int> prefix = prefixSum(arr);
    cout << "Prefix Sum Array: ";
    for (int num : prefix) cout << num << " ";
    cout << endl;

    // Sparse Matrix Input
    int rows, cols;
    cout << "\nEnter the number of rows and columns for the matrix: ";
    cin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    cout << "Enter the matrix elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }

    // Convert to Sparse Representation
    vector<SparseElement> sparseMatrix = convertToSparse(matrix);
    displaySparseMatrix(sparseMatrix);

    return 0;
}
