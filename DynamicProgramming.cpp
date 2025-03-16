#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// 1. Coin Change (Min coins to make amount)
int minCoins(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// 2. 0/1 Knapsack Problem
int knapsack01(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

// 3. Fractional Knapsack
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

// 4. Rod Cutting Problem
int rodCutting(vector<int>& prices, int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] = max(dp[i], prices[j] + dp[i - j - 1]);
        }
    }
    return dp[n];
}

// 5. Subset Sum Problem
bool subsetSum(vector<int>& nums, int sum) {
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; i++) dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (nums[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][sum];
}

// 6. Bellman-Ford Algorithm (Shortest path with negative edges)
void bellmanFord(vector<vector<int>>& edges, int V, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (auto edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    cout << "Bellman-Ford Shortest Paths from " << src << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "To " << i << " -> Distance: " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

// 7. Floyd-Warshall Algorithm (All-Pairs Shortest Paths)
void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph;
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cout << "Floyd-Warshall Shortest Paths:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << (dist[i][j] == INT_MAX ? "INF" : to_string(dist[i][j])) << " ";
        }
        cout << endl;
    }
}

// Main Function
int main() {
    cout << "Dynamic Programming Algorithms Implemented!\n";

    // Coin Change
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << "Min Coins to Make " << amount << ": " << minCoins(coins, amount) << endl;

    // 0/1 Knapsack
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int W = 5;
    cout << "0/1 Knapsack Max Value: " << knapsack01(weights, values, W) << endl;

    // Fractional Knapsack
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    cout << "Fractional Knapsack Max Value: " << fractionalKnapsack(items, 50) << endl;

    // Rod Cutting
    vector<int> rodPrices = {1, 5, 8, 9, 10, 17, 17, 20};
    cout << "Rod Cutting Max Profit: " << rodCutting(rodPrices, rodPrices.size()) << endl;

    // Subset Sum
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;
    cout << "Subset Sum " << target << " Exists: " << (subsetSum(nums, target) ? "Yes" : "No") << endl;

    // Bellman-Ford
    vector<vector<int>> edges = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};
    int V = 5, src = 0;
    bellmanFord(edges, V, src);

    // Floyd-Warshall
    vector<vector<int>> graph = {
        {0, 3, INT_MAX, 5},
        {2, 0, INT_MAX, 4},
        {INT_MAX, 1, 0, INT_MAX},
        {INT_MAX, INT_MAX, 2, 0}};
    floydWarshall(graph, 4);

    return 0;
}
