#include <iostream>
#include <cstdint>
using namespace std;

// Node structure for XOR Linked List
struct Node {
    int data;
    Node* npx; // XOR of next and previous node addresses

    Node(int val) {
        data = val;
        npx = nullptr;
    }
};

// XOR utility function
Node* XOR(Node* a, Node* b) {
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
}

class XORLinkedList {
private:
    Node* head;
    Node* tail;

public:
    XORLinkedList() {
        head = tail = nullptr;
    }

    // Insert at the beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->npx = head;
            head->npx = XOR(newNode, head->npx);
            head = newNode;
        }
    }

    // Insert at the end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->npx = XOR(tail->npx, newNode);
            newNode->npx = tail;
            tail = newNode;
        }
    }

    // Insert at a specific position
    void insertAtPosition(int val, int pos) {
        if (pos == 1) {
            insertAtBeginning(val);
            return;
        }

        Node* prev = nullptr, *curr = head, *next;
        int count = 1;
        while (curr && count < pos - 1) {
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
            count++;
        }

        if (!curr) {
            cout << "Position out of range. Inserting at the end." << endl;
            insertAtEnd(val);
            return;
        }

        Node* newNode = new Node(val);
        next = XOR(prev, curr->npx);
        newNode->npx = XOR(curr, next);
        curr->npx = XOR(prev, newNode);
        if (next) {
            next->npx = XOR(newNode, XOR(curr, next->npx));
        }
    }

    // Forward Traversal
    void printForward() {
        Node* curr = head;
        Node* prev = nullptr;
        Node* next;

        cout << "Forward: ";
        while (curr) {
            cout << curr->data << " ";
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        cout << endl;
    }

    // Reverse Traversal
    void printReverse() {
        Node* curr = tail;
        Node* next = nullptr;
        Node* prev;

        cout << "Reverse: ";
        while (curr) {
            cout << curr->data << " ";
            prev = XOR(next, curr->npx);
            next = curr;
            curr = prev;
        }
        cout << endl;
    }

    // Find a specific node
    bool find(int val) {
        Node* curr = head;
        Node* prev = nullptr;
        Node* next;

        while (curr) {
            if (curr->data == val) {
                return true;
            }
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        return false;
    }

    // Delete at a specific position
    void deleteAtPosition(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* prev = nullptr, *curr = head, *next;
        int count = 1;
        while (curr && count < pos) {
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
            count++;
        }

        if (!curr) {
            cout << "Position out of range." << endl;
            return;
        }

        next = XOR(prev, curr->npx);
        if (prev) {
            prev->npx = XOR(XOR(prev->npx, curr), next);
        } else {
            head = next;
        }

        if (next) {
            next->npx = XOR(prev, XOR(curr, next->npx));
        } else {
            tail = prev;
        }

        delete curr;
    }
};

int main() {
    XORLinkedList xorList;
    
    xorList.insertAtEnd(10);
    xorList.insertAtEnd(20);
    xorList.insertAtEnd(30);
    xorList.insertAtEnd(40);

    xorList.printForward();
    xorList.printReverse();

    xorList.insertAtBeginning(5);
    xorList.insertAtPosition(25, 3);

    xorList.printForward();

    cout << "Finding 20: " << (xorList.find(20) ? "Found" : "Not Found") << endl;
    cout << "Finding 50: " << (xorList.find(50) ? "Found" : "Not Found") << endl;

    xorList.deleteAtPosition(3);
    xorList.printForward();

    return 0;
}
