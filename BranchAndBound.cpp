#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

// --- 0/1 Knapsack Problem using Branch and Bound ---
struct KnapsackNode {
    int level, profit, weight, bound;
};

bool compareItems(const pair<int, int>& a, const pair<int, int>& b) {
    return (double)a.second / a.first > (double)b.second / b.first;
}

int bound(KnapsackNode u, int W, vector<pair<int, int>>& items) {
    if (u.weight >= W) return 0;
    int profit_bound = u.profit;
    int j = u.level + 1, totalWeight = u.weight;
    
    while (j < items.size() && totalWeight + items[j].first <= W) {
        totalWeight += items[j].first;
        profit_bound += items[j].second;
        j++;
    }
    
    if (j < items.size()) 
        profit_bound += (W - totalWeight) * (double)items[j].second / items[j].first;

    return profit_bound;
}

int knapsack(int W, vector<pair<int, int>>& items) {
    sort(items.begin(), items.end(), compareItems);
    queue<KnapsackNode> Q;
    KnapsackNode u, v;
    
    u.level = -1, u.profit = u.weight = 0;
    Q.push(u);
    
    int maxProfit = 0;
    while (!Q.empty()) {
        u = Q.front(); Q.pop();
        if (u.level == items.size() - 1) continue;
        
        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].first;
        v.profit = u.profit + items[v.level].second;
        
        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;
        
        v.bound = bound(v, W, items);
        if (v.bound > maxProfit)
            Q.push(v);

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, W, items);
        if (v.bound > maxProfit)
            Q.push(v);
    }
    return maxProfit;
}

// --- Travelling Salesman Problem (TSP) using Branch and Bound ---
const int INF = 1e9;
int n = 4; 
int tspMatrix[4][4] = { {INF, 10, 15, 20}, {10, INF, 35, 25}, {15, 35, INF, 30}, {20, 25, 30, INF} };
vector<int> bestPath;
int minCost = INT_MAX;

void tsp(vector<int>& path, vector<bool>& visited, int cost, int level) {
    if (level == n) {
        cost += tspMatrix[path.back()][path[0]];
        if (cost < minCost) {
            minCost = cost;
            bestPath = path;
        }
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(i);
            tsp(path, visited, cost + tspMatrix[path[path.size()-2]][i], level + 1);
            visited[i] = false;
            path.pop_back();
        }
    }
}

// --- N-Queens Problem using Branch and Bound ---
#define N 8
int board[N];

bool isSafe(int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[i] == row || abs(board[i] - row) == abs(i - col))
            return false;
    return true;
}

void solveNQueens(int col) {
    if (col == N) {
        for (int i = 0; i < N; i++) cout << board[i] << " ";
        cout << endl;
        return;
    }
    for (int row = 0; row < N; row++) {
        if (isSafe(row, col)) {
            board[col] = row;
            solveNQueens(col + 1);
        }
    }
}

// --- Job Assignment Problem using Branch and Bound ---
int jobMatrix[4][4] = {{9, 2, 7, 8}, {6, 4, 3, 7}, {5, 8, 1, 8}, {7, 6, 9, 4}};
bool assigned[4] = {false};
int minJobCost = INT_MAX;

void assignJobs(int level, int cost) {
    if (level == 4) {
        minJobCost = min(minJobCost, cost);
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (!assigned[i]) {
            assigned[i] = true;
            assignJobs(level + 1, cost + jobMatrix[level][i]);
            assigned[i] = false;
        }
    }
}

// --- Longest Path in a DAG using Branch and Bound ---
vector<vector<pair<int, int>>> graph;
vector<int> topoSort, dist;
bool visitedDAG[6];

void topologicalSort(int node) {
    visitedDAG[node] = true;
    for (auto& neighbor : graph[node])
        if (!visitedDAG[neighbor.first])
            topologicalSort(neighbor.first);
    topoSort.push_back(node);
}

void longestPathDAG(int start) {
    reverse(topoSort.begin(), topoSort.end());
    dist.assign(6, -INF);
    dist[start] = 0;
    
    for (int node : topoSort) {
        if (dist[node] != -INF) {
            for (auto& neighbor : graph[node])
                dist[neighbor.first] = max(dist[neighbor.first], dist[node] + neighbor.second);
        }
    }
}

// --- Graph Coloring Problem using Branch and Bound ---
#define V 4
vector<int> color(V, 0);
bool isSafeColoring(int v, int c, vector<vector<int>>& graph) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

bool graphColoring(int v, int m, vector<vector<int>>& graph) {
    if (v == V) return true;
    for (int c = 1; c <= m; c++) {
        if (isSafeColoring(v, c, graph)) {
            color[v] = c;
            if (graphColoring(v + 1, m, graph)) return true;
            color[v] = 0;
        }
    }
    return false;
}

// --- Main Function ---
int main() {
    cout << "Branch and Bound Algorithms Implemented!" << endl;

    // 0/1 Knapsack
    vector<pair<int, int>> items = {{2, 40}, {3, 50}, {4, 70}, {5, 80}};
    cout << "Max Knapsack Profit: " << knapsack(5, items) << endl;

    // TSP
    vector<int> path = {0};
    vector<bool> visited(n, false);
    visited[0] = true;
    tsp(path, visited, 0, 1);
    cout << "TSP Minimum Cost: " << minCost << endl;

    // N-Queens
    cout << "N-Queens Solutions:" << endl;
    solveNQueens(0);

    // Job Assignment
    assignJobs(0, 0);
    cout << "Minimum Job Assignment Cost: " << minJobCost << endl;

    // Longest Path in DAG
    longestPathDAG(1);
    cout << "Longest Path from Node 1: " << dist[5] << endl;

    // Graph Coloring
    vector<vector<int>> graph = {{0, 1, 1, 0}, {1, 0, 1, 1}, {1, 1, 0, 1}, {0, 1, 1, 0}};
    cout << "Graph Coloring Possible: " << graphColoring(0, 3, graph) << endl;

    return 0;
}
