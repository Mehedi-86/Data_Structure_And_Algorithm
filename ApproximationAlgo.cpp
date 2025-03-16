#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <cstdlib>
#include <climits>
using namespace std;

// Traveling Salesman Problem (TSP) Approximation using MST
int tspApproximation(vector<vector<int>> &dist) {
    int n = dist.size();
    vector<int> visited(n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0}); // {weight, node}
    int mstCost = 0, edges = 0;

    while (!pq.empty() && edges < n) {
        auto [w, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = 1;
        mstCost += w;
        edges++;

        for (int v = 0; v < n; v++)
            if (!visited[v] && dist[u][v])
                pq.push({dist[u][v], v});
    }

    return 2 * mstCost; // Approximate TSP cost using MST
}

// Vertex Cover Approximation using a Greedy Approach
int vertexCoverApproximation(int n, vector<pair<int, int>> &edges) {
    unordered_set<int> cover;
    unordered_set<int> used;
    for (auto &[u, v] : edges) {
        if (used.count(u) || used.count(v)) continue;
        cover.insert(u);
        cover.insert(v);
        used.insert(u);
        used.insert(v);
    }
    return cover.size();
}

// Fractional Knapsack Approximation
double knapsackApproximation(int W, vector<pair<int, int>> &items) {
    sort(items.begin(), items.end(), [](auto &a, auto &b) {
        return (double)a.first / a.second > (double)b.first / b.second;
    });

    double maxValue = 0;
    for (auto &[val, wt] : items) {
        if (W >= wt) {
            W -= wt;
            maxValue += val;
        } else {
            maxValue += val * ((double)W / wt);
            break;
        }
    }
    return maxValue;
}

// Makespan Minimization (LPT Scheduling)
int makespanMinimization(int m, vector<int> &jobs) {
    sort(jobs.rbegin(), jobs.rend()); // Sort jobs in descending order
    vector<int> machineLoad(m, 0);

    for (int job : jobs) {
        *min_element(machineLoad.begin(), machineLoad.end()) += job;
    }

    return *max_element(machineLoad.begin(), machineLoad.end());
}

// Max-Cut Approximation using Random Partitioning
int maxCutApproximation(int n, vector<pair<int, int>> &edges) {
    vector<int> partition(n);
    for (int i = 0; i < n; i++) partition[i] = rand() % 2;
    int cutSize = 0;
    for (auto &[u, v] : edges) {
        if (partition[u] != partition[v]) cutSize++;
    }
    return cutSize;
}

// Graph Coloring Approximation (Greedy)
int graphColoringApproximation(int n, vector<pair<int, int>> &edges) {
    vector<int> color(n, -1);
    for (int u = 0; u < n; u++) {
        set<int> usedColors;
        for (auto &[v1, v2] : edges) {
            if (v1 == u && color[v2] != -1) usedColors.insert(color[v2]);
            if (v2 == u && color[v1] != -1) usedColors.insert(color[v1]);
        }
        for (int c = 0; ; c++) {
            if (!usedColors.count(c)) {
                color[u] = c;
                break;
            }
        }
    }
    return *max_element(color.begin(), color.end()) + 1;
}

// Main function to execute all Approximation Algorithms
int main() {
    cout << "Starting Approximation Algorithms...\n";

    // 1. Traveling Salesman Problem (TSP)
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter distance matrix:\n";
    for (auto &row : dist) for (auto &x : row) cin >> x;
    cout << "TSP Approximation Output: Approximate cost using MST: " << tspApproximation(dist) << "\n";

    // 2. Vertex Cover
    int v, e;
    cout << "Enter number of vertices and edges: ";
    cin >> v >> e;
    vector<pair<int, int>> edges(e);
    cout << "Enter edges (u v):\n";
    for (auto &edge : edges) cin >> edge.first >> edge.second;
    cout << "Vertex Cover Approximation Output: Approximate Cover Size: " << vertexCoverApproximation(v, edges) << "\n";

    // 3. Knapsack Problem
    int W, itemsCount;
    cout << "Enter number of items and knapsack capacity: ";
    cin >> itemsCount >> W;
    vector<pair<int, int>> items(itemsCount);
    cout << "Enter values and weights:\n";
    for (auto &item : items) cin >> item.first >> item.second;
    cout << "Knapsack Approximation Output: Approximate max value: " << knapsackApproximation(W, items) << "\n";

    // 4. Makespan Minimization
    int m, jobCount;
    cout << "Enter number of jobs and machines: ";
    cin >> jobCount >> m;
    vector<int> jobs(jobCount);
    cout << "Enter processing times of jobs:\n";
    for (int &job : jobs) cin >> job;
    cout << "Makespan Minimization Output: Approximate Makespan: " << makespanMinimization(m, jobs) << "\n";

    // 5. Max-Cut Problem
    cout << "Enter number of vertices and edges: ";
    cin >> v >> e;
    edges.resize(e);
    cout << "Enter edges (u v):\n";
    for (auto &edge : edges) cin >> edge.first >> edge.second;
    cout << "Max-Cut Approximation Output: Approximate Cut Size: " << maxCutApproximation(v, edges) << "\n";

    // 6. Graph Coloring Approximation
    cout << "Enter number of vertices and edges: ";
    cin >> v >> e;
    edges.resize(e);
    cout << "Enter edges (u v):\n";
    for (auto &edge : edges) cin >> edge.first >> edge.second;
    cout << "Graph Coloring Approximation Output: Approximate Chromatic Number: " << graphColoringApproximation(v, edges) << "\n";

    cout << "All Approximation Algorithms Executed!\n";
    return 0;
}
