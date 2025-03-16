#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] > heap[index]) {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;

        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() {}

    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int getMin() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        return heap[0];
    }

    void deleteMin() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void buildHeap(vector<int> &arr) {
        heap = arr;
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void heapSort(vector<int> &arr) {
        buildHeap(arr);
        for (int i = heap.size() - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            heap.pop_back();
            heapifyDown(0);
        }
        arr = heap;
    }

    void printHeap() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(40);
    heap.insert(5);

    cout << "Min Heap: ";
    heap.printHeap();

    cout << "Min Element: " << heap.getMin() << endl;

    heap.deleteMin();
    cout << "Heap after deleting min: ";
    heap.printHeap();

    vector<int> arr = {50, 20, 10, 40, 30};
    heap.buildHeap(arr);
    cout << "Heap built from array: ";
    heap.printHeap();

    heap.heapSort(arr);
    cout << "Heap Sorted Array: ";
    for (int val : arr) cout << val << " ";
    cout << endl;

    return 0;
}
