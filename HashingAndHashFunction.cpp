#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

class HashTable {
private:
    int tableSize;
    vector<list<int>> table;

    // 1. Modulo Hash Function
    int moduloHash(int key) {
        return key % tableSize;
    }

    // 2. Multiplication Hash Function
    int multiplicationHash(int key) {
        double A = 0.6180339887; // Knuth's constant
        return int(tableSize * fmod(key * A, 1));
    }

    // 3. Mid-Square Hash Function
    int midSquareHash(int key) {
        int squared = key * key;
        int mid = (squared / 100) % tableSize; // Extract middle digits
        return mid % tableSize;
    }

    // 4. Folding Hash Function
    int foldingHash(int key) {
        int sum = 0;
        while (key > 0) {
            sum += key % 1000; // Taking 3-digit parts
            key /= 1000;
        }
        return sum % tableSize;
    }

public:
    HashTable(int size) : tableSize(size) {
        table.resize(tableSize);
    }

    // Insert using selected hash function
    void insert(int key, int method = 1) {
        int index;
        switch (method) {
            case 1: index = moduloHash(key); break;
            case 2: index = multiplicationHash(key); break;
            case 3: index = midSquareHash(key); break;
            case 4: index = foldingHash(key); break;
            default: index = moduloHash(key); break;
        }
        table[index].push_back(key);
    }

    // Display hash table
    void display() {
        for (int i = 0; i < tableSize; i++) {
            cout << "Bucket " << i << ": ";
            for (int num : table[i]) {
                cout << num << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

// 5. String Hash Function (Polynomial Rolling Hash)
unsigned long long stringHash(string str, int tableSize) {
    const int p = 31; // Prime base
    const int m = 1e9 + 9; // Large prime number
    unsigned long long hashValue = 0, p_pow = 1;
    
    for (char c : str) {
        hashValue = (hashValue + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hashValue % tableSize;
}

// Driver Code
int main() {
    int tableSize = 10;
    HashTable ht(tableSize);

    // Insert elements using different hash functions
    vector<int> keys = {18, 41, 22, 44, 59, 32, 31, 73, 99};
    
    cout << "Hash Table using Modulo Hashing:\n";
    for (int key : keys) ht.insert(key, 1);
    ht.display();

    ht = HashTable(tableSize);
    cout << "\nHash Table using Multiplication Hashing:\n";
    for (int key : keys) ht.insert(key, 2);
    ht.display();

    ht = HashTable(tableSize);
    cout << "\nHash Table using Mid-Square Hashing:\n";
    for (int key : keys) ht.insert(key, 3);
    ht.display();

    ht = HashTable(tableSize);
    cout << "\nHash Table using Folding Hashing:\n";
    for (int key : keys) ht.insert(key, 4);
    ht.display();

    // String Hashing Example
    string testString = "hello";
    cout << "\nString Hash ('hello') using Polynomial Rolling Hash: " 
         << stringHash(testString, tableSize) << endl;

    return 0;
}
