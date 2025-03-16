#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

// 1️⃣ **Activity Selection Problem**
struct Activity {
    int start, end;
};
bool compare(Activity a, Activity b) {
    return a.end < b.end;
}
void activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compare);
    cout << "Activity Selection Output:\nSelected Activities: (start, end) -> ";
    int lastEnd = activities[0].end;
    cout << "(" << activities[0].start << ", " << activities[0].end << ") ";
    int count = 1;
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastEnd) {
            cout << "(" << activities[i].start << ", " << activities[i].end << ") ";
            count++;
            lastEnd = activities[i].end;
        }
    }
    cout << "\nMaximum Activities: " << count << "\n\n";
}

// 2️⃣ **Huffman Encoding**
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};
void printHuffmanCodes(HuffmanNode* root, string code) {
    if (!root) return;
    if (root->data != '$') cout << root->data << ": " << code << endl;
    printHuffmanCodes(root->left, code + "0");
    printHuffmanCodes(root->right, code + "1");
}
void huffmanCoding(vector<char> chars, vector<int> freqs) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (int i = 0; i < chars.size(); i++)
        pq.push(new HuffmanNode(chars[i], freqs[i]));
    while (pq.size() > 1) {
        HuffmanNode *left = pq.top(); pq.pop();
        HuffmanNode *right = pq.top(); pq.pop();
        HuffmanNode *node = new HuffmanNode('$', left->freq + right->freq);
        node->left = left; node->right = right;
        pq.push(node);
    }
    cout << "Huffman Encoding Output:\n";
    printHuffmanCodes(pq.top(), "");
    cout << endl;
}

// 3️⃣ **Job Scheduling Problem**
struct Job {
    char id;
    int deadline, profit;
};
bool jobCompare(Job a, Job b) {
    return a.profit > b.profit;
}
void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), jobCompare);
    int maxDeadline = 0;
    for (auto job : jobs) maxDeadline = max(maxDeadline, job.deadline);
    vector<char> schedule(maxDeadline, '-');
    int totalProfit = 0;
    for (auto job : jobs) {
        for (int j = job.deadline - 1; j >= 0; j--) {
            if (schedule[j] == '-') {
                schedule[j] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }
    cout << "Job Scheduling Output:\nScheduled Jobs: ";
    for (char j : schedule) if (j != '-') cout << j << " ";
    cout << "\nTotal Profit: " << totalProfit << "\n\n";
}

// 4️⃣ **Fractional Knapsack**
struct Item {
    int weight, value;
};
bool knapsackCompare(Item a, Item b) {
    return (double)a.value / a.weight > (double)b.value / b.weight;
}
double fractionalKnapsack(vector<Item>& items, int W) {
    sort(items.begin(), items.end(), knapsackCompare);
    double totalValue = 0.0;
    for (auto item : items) {
        if (W >= item.weight) {
            totalValue += item.value;
            W -= item.weight;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            break;
        }
    }
    return totalValue;
}

// 5️⃣ **Prim’s Algorithm**
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> key(V, INT_MAX), parent(V, -1);
    vector<bool> inMST(V, false);
    key[0] = 0;
    cout << "Prim's MST Output:\n";
    for (int count = 0; count < V - 1; count++) {
        int u = min_element(key.begin(), key.end()) - key.begin();
        inMST[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
    }
    cout << endl;
}

// 6️⃣ **Kruskal’s Algorithm**
struct Edge {
    int u, v, weight;
};
bool edgeCompare(Edge a, Edge b) {
    return a.weight < b.weight;
}
void kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), edgeCompare);
    cout << "Kruskal's MST Output:\n";
    for (auto e : edges) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }
    cout << endl;
}

// 7️⃣ **Dijkstra’s Algorithm**
void dijkstra(vector<vector<int>>& graph, int V, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    cout << "Dijkstra's Shortest Paths from Source " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "To " << i << " -> Distance: " << dist[i] << endl;
    cout << endl;
}

// 8️⃣ **Coin Change Problem**
void coinChange(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend());
    cout << "Coin Change Output:\nCoins used: ";
    for (int coin : coins) {
        int count = amount / coin;
        if (count > 0) cout << coin << "x" << count << " ";
        amount -= count * coin;
    }
    cout << endl;
}

int main() {
    cout << "Greedy Algorithms Implemented!\n\n";

    // 1️⃣ Activity Selection
    vector<Activity> activities = {{1, 3}, {2, 5}, {4, 6}, {6, 7}, {5, 9}, {8, 9}};
    activitySelection(activities);

    // 2️⃣ Huffman Encoding
    vector<char> chars = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freqs = {5, 9, 12, 13, 16, 45};
    huffmanCoding(chars, freqs);

    // 3️⃣ Job Scheduling
    vector<Job> jobs = {{'A', 2, 100}, {'B', 1, 90}, {'C', 2, 10}, {'D', 1, 20}, {'E', 3, 50}};
    jobScheduling(jobs);

    // 4️⃣ Fractional Knapsack
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    cout << "Max Value in Knapsack: " << fractionalKnapsack(items, 50) << "\n\n";

    // 5️⃣ Prim’s Algorithm
    vector<vector<int>> primGraph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}};
    primMST(primGraph, 5);

    // 6️⃣ Kruskal’s Algorithm
    vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    kruskalMST(edges, 4);

    // 7️⃣ Dijkstra’s Algorithm
    vector<vector<int>> dijkstraGraph = {
        {0, 7, 9, 0, 0, 14},
        {7, 0, 10, 15, 0, 0},
        {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0},
        {0, 0, 0, 6, 0, 9},
        {14, 0, 2, 0, 9, 0}};
    dijkstra(dijkstraGraph, 6, 0);

    // 8️⃣ Coin Change Problem
    vector<int> coins = {1, 2, 5, 10, 20, 50};
    coinChange(coins, 93);

    return 0;
}