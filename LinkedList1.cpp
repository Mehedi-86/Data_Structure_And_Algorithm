#include <iostream>

using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next;
};

// Function to insert at the beginning
void insertAtBeginning(Node*& head, int value) {
    Node* newNode = new Node{value, head};
    head = newNode;
}

// Function to insert at the end
void insertAtEnd(Node*& head, int value) {
    Node* newNode = new Node{value, nullptr};
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

// Function to insert at a specific position
void insertAtPosition(Node*& head, int value, int position) {
    if (position <= 1) {
        insertAtBeginning(head, value);
        return;
    }

    Node* newNode = new Node{value, nullptr};
    Node* temp = head;
    for (int i = 1; temp && i < position - 1; i++)
        temp = temp->next;

    if (!temp) {
        cout << "Position out of range, inserting at end.\n";
        insertAtEnd(head, value);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Function to delete from the beginning
void deleteFromBeginning(Node*& head) {
    if (!head) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

// Function to delete from the end
void deleteFromEnd(Node*& head) {
    if (!head) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next->next)
        temp = temp->next;
    
    delete temp->next;
    temp->next = nullptr;
}

// Function to delete from a specific position
void deleteFromPosition(Node*& head, int position) {
    if (!head) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }
    if (position == 1) {
        deleteFromBeginning(head);
        return;
    }

    Node* temp = head;
    for (int i = 1; temp->next && i < position - 1; i++)
        temp = temp->next;

    if (!temp->next) {
        cout << "Position out of range.\n";
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
}

// Function to display the linked list
void displayList(Node* head) {
    if (!head) {
        cout << "List is empty.\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// Main function to handle user input
int main() {
    Node* head = nullptr;
    int choice, value, position;

    do {
        cout << "\nLinked List Operations:\n";
        cout << "1. Insert at Beginning\n2. Insert at End\n3. Insert at Position\n";
        cout << "4. Delete from Beginning\n5. Delete from End\n6. Delete from Position\n";
        cout << "7. Display List\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                insertAtBeginning(head, value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                insertAtEnd(head, value);
                break;
            case 3:
                cout << "Enter value and position: ";
                cin >> value >> position;
                insertAtPosition(head, value, position);
                break;
            case 4:
                deleteFromBeginning(head);
                break;
            case 5:
                deleteFromEnd(head);
                break;
            case 6:
                cout << "Enter position: ";
                cin >> position;
                deleteFromPosition(head, position);
                break;
            case 7:
                displayList(head);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 8);

    return 0;
}
