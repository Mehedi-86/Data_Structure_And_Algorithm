#include <iostream>

using namespace std;

// Node structure for BST
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function to insert a node in BST
Node* insert(Node* root, int value) {
    if (root == nullptr) return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// Function to search for a value in BST
bool search(Node* root, int value) {
    if (!root) return false;
    if (root->data == value) return true;

    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

// Helper function to find the minimum value node
Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

// Function to delete a node in BST
Node* deleteNode(Node* root, int value) {
    if (!root) return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        // Node with one child or no child
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get inorder successor (smallest in right subtree)
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder Traversal (Left -> Root -> Right)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Preorder Traversal (Root -> Left -> Right)
void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal (Left -> Right -> Root)
void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

// Main function to interact with BST
int main() {
    Node* root = nullptr;
    int choice, value;

    do {
        cout << "\nBinary Search Tree Operations:\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n";
        cout << "5. Preorder Traversal\n6. Postorder Traversal\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Value found in BST.\n";
                else
                    cout << "Value not found in BST.\n";
                break;
            case 4:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;
            case 6:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 7);

    return 0;
}
