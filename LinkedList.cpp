#include <iostream>

using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next;
};

// Node structure for Doubly Linked List
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
};

// Node structure for Circular Linked List
struct CNode {
    int data;
    CNode* next;
};

// Function to sort a Singly Linked List using Bubble Sort
void sortSingly(Node*& head) {
    if (!head) return;
    bool swapped;
    Node* ptr1;
    Node* lptr = nullptr;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to search for a value in Singly Linked List
bool searchSingly(Node* head, int key) {
    while (head) {
        if (head->data == key)
            return true;
        head = head->next;
    }
    return false;
}

// Function to sort a Doubly Linked List using Bubble Sort
void sortDoubly(DNode*& head) {
    if (!head) return;
    bool swapped;
    DNode* ptr1;
    DNode* lptr = nullptr;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to search for a value in Doubly Linked List
bool searchDoubly(DNode* head, int key) {
    while (head) {
        if (head->data == key)
            return true;
        head = head->next;
    }
    return false;
}

// Function to sort a Circular Linked List using Bubble Sort
void sortCircular(CNode*& head) {
    if (!head) return;
    bool swapped;
    CNode* ptr1;
    CNode* lptr = nullptr;
    do {
        swapped = false;
        ptr1 = head;
        do {
            if (ptr1->next != head && ptr1->data > ptr1->next->data) {
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        } while (ptr1->next != lptr && ptr1->next != head);
        lptr = ptr1;
    } while (swapped);
}

// Function to search for a value in Circular Linked List
bool searchCircular(CNode* head, int key) {
    if (!head) return false;
    CNode* temp = head;
    do {
        if (temp->data == key)
            return true;
        temp = temp->next;
    } while (temp != head);
    return false;
}

// Function to handle Singly Linked List operations
void singlyLinkedList() {
    Node* head = nullptr;
    Node* tail = nullptr;

    int n;
    cout << "Enter the number of elements in the Singly Linked List: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value: ";
        cin >> value;
        Node* newNode = new Node{value, nullptr};

        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    sortSingly(head);

    cout << "Sorted Singly Linked List: ";
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;

    int key;
    cout << "Enter a value to search in Singly Linked List: ";
    cin >> key;
    if (searchSingly(head, key))
        cout << "Value found in Singly Linked List.\n";
    else
        cout << "Value not found in Singly Linked List.\n";
}

// Function to handle Doubly Linked List operations
void doublyLinkedList() {
    DNode* head = nullptr;
    DNode* tail = nullptr;

    int n;
    cout << "Enter the number of elements in the Doubly Linked List: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value: ";
        cin >> value;
        DNode* newNode = new DNode{value, nullptr, nullptr};

        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    sortDoubly(head);

    cout << "Sorted Doubly Linked List (Forward): ";
    DNode* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;

    int key;
    cout << "Enter a value to search in Doubly Linked List: ";
    cin >> key;
    if (searchDoubly(head, key))
        cout << "Value found in Doubly Linked List.\n";
    else
        cout << "Value not found in Doubly Linked List.\n";
}

// Function to handle Circular Linked List operations
void circularLinkedList() {
    CNode* head = nullptr;
    CNode* tail = nullptr;

    int n;
    cout << "Enter the number of elements in the Circular Linked List: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value: ";
        cin >> value;
        CNode* newNode = new CNode{value, nullptr};

        if (!head) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    sortCircular(head);

    cout << "Sorted Circular Linked List: ";
    CNode* temp = head;
    if (head) {
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
    }
    cout << endl;

    int key;
    cout << "Enter a value to search in Circular Linked List: ";
    cin >> key;
    if (searchCircular(head, key))
        cout << "Value found in Circular Linked List.\n";
    else
        cout << "Value not found in Circular Linked List.\n";
}

// Main function
int main() {
    int choice;
    do {
        cout << "\nChoose Linked List Type:\n";
        cout << "1. Singly Linked List\n2. Doubly Linked List\n3. Circular Linked List\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                singlyLinkedList();
                break;
            case 2:
                doublyLinkedList();
                break;
            case 3:
                circularLinkedList();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
