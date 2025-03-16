#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V + 1); // To handle 1-based indexing
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v); // Directed graph (u → v)
    }

    void bfs(int start) {
        vector<bool> visited(V + 1, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void dfsUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(int start) {
        vector<bool> visited(V + 1, false);
        dfsUtil(start, visited);
        cout << endl;
    }

    void topologicalSort() {
        vector<int> inDegree(V + 1, 0);
        for (int i = 1; i <= V; i++) {
            for (int neighbor : adj[i]) {
                inDegree[neighbor]++;
            }
        }

        queue<int> q;
        for (int i = 1; i <= V; i++) {
            if (inDegree[i] == 0) q.push(i);
        }

        vector<int> topoOrder;
        int count = 0; // Count of processed nodes
        while (!q.empty()) {
            int node = q.front(); q.pop();
            topoOrder.push_back(node);
            count++;
            for (int neighbor : adj[node]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (count != V) {
            cout << "Topological sorting not possible (Graph has a cycle)\n";
            return;
        }

        cout << "Topological Order: ";
        for (int node : topoOrder) cout << node << " ";
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    Graph g(V);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "BFS starting from node 1: ";
    g.bfs(1);

    cout << "DFS starting from node 1: ";
    g.dfs(1);

    cout << "Performing Topological Sort:\n";
    g.topologicalSort();
    
    return 0;
}
