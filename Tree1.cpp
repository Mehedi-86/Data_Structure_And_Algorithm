#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//------------------ AVL TREE ------------------//
struct AVLNode {
    int data, height;
    AVLNode *left, *right;
    AVLNode(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(AVLNode* node) { return node ? node->height : 0; }
int getBalanceFactor(AVLNode* node) { return node ? getHeight(node->left) - getHeight(node->right) : 0; }

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLNode* insertAVL(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);
    if (key < node->data) node->left = insertAVL(node->left, key);
    else node->right = insertAVL(node->right, key);
    
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->data) return rotateRight(node);
    if (balance < -1 && key > node->right->data) return rotateLeft(node);
    if (balance > 1 && key > node->left->data) { node->left = rotateLeft(node->left); return rotateRight(node); }
    if (balance < -1 && key < node->right->data) { node->right = rotateRight(node->right); return rotateLeft(node); }

    return node;
}

void inorderAVL(AVLNode* root) {
    if (root) { inorderAVL(root->left); cout << root->data << " "; inorderAVL(root->right); }
}

//------------------ 2-3 TREE ------------------//
struct TwoThreeNode {
    int val1, val2;
    TwoThreeNode *left, *middle, *right;
    bool isTwoNode;
    TwoThreeNode(int v1) : val1(v1), val2(0), left(nullptr), middle(nullptr), right(nullptr), isTwoNode(true) {}
};

void inorderTwoThree(TwoThreeNode* root) {
    if (!root) return;
    inorderTwoThree(root->left);
    cout << root->val1 << " ";
    inorderTwoThree(root->middle);
    if (!root->isTwoNode) cout << root->val2 << " ";
    inorderTwoThree(root->right);
}

TwoThreeNode* insertTwoThree(TwoThreeNode* root, int val) {
    if (!root) return new TwoThreeNode(val);
    if (val < root->val1) root->left = insertTwoThree(root->left, val);
    else if (root->isTwoNode || val < root->val2) root->middle = insertTwoThree(root->middle, val);
    else root->right = insertTwoThree(root->right, val);
    return root;
}

//------------------ B-TREE ------------------//
#define MAX 2
struct BTreeNode {
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;
    BTreeNode(bool _leaf) : leaf(_leaf) {}
};

void traverseBTree(BTreeNode* root) {
    if (!root) return;
    for (size_t i = 0; i < root->keys.size(); i++) {
        if (i < root->children.size()) traverseBTree(root->children[i]);
        cout << root->keys[i] << " ";
    }
    if (!root->children.empty()) traverseBTree(root->children.back());
}

BTreeNode* insertBTree(BTreeNode* root, int k) {
    if (!root) return new BTreeNode(true);
    root->keys.push_back(k);
    sort(root->keys.begin(), root->keys.end());
    return root;
}

//------------------ HEAP ------------------//
void heapExample(priority_queue<int> maxHeap, priority_queue<int, vector<int>, greater<int>> minHeap) {
    cout << "Max Heap: ";
    while (!maxHeap.empty()) { cout << maxHeap.top() << " "; maxHeap.pop(); }
    cout << endl;
    
    cout << "Min Heap: ";
    while (!minHeap.empty()) { cout << minHeap.top() << " "; minHeap.pop(); }
    cout << endl;
}

//------------------ MAIN FUNCTION ------------------//
int main() {
    AVLNode* avlRoot = nullptr;
    int n, val;
    cout << "Enter number of AVL tree elements: "; cin >> n;
    for (int i = 0; i < n; i++) { cin >> val; avlRoot = insertAVL(avlRoot, val); }
    cout << "AVL Tree: "; inorderAVL(avlRoot); cout << endl;
    
    TwoThreeNode* twoThreeRoot = nullptr;
    cout << "Enter number of 2-3 Tree elements: "; cin >> n;
    for (int i = 0; i < n; i++) { cin >> val; twoThreeRoot = insertTwoThree(twoThreeRoot, val); }
    cout << "2-3 Tree: "; inorderTwoThree(twoThreeRoot); cout << endl;
    
    BTreeNode* bTreeRoot = nullptr;
    cout << "Enter number of B-Tree elements: "; cin >> n;
    for (int i = 0; i < n; i++) { cin >> val; bTreeRoot = insertBTree(bTreeRoot, val); }
    cout << "B-Tree: "; traverseBTree(bTreeRoot); cout << endl;
    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    cout << "Enter number of heap elements: "; cin >> n;
    for (int i = 0; i < n; i++) { cin >> val; maxHeap.push(val); minHeap.push(val); }
    heapExample(maxHeap, minHeap);
    
    return 0;
}
