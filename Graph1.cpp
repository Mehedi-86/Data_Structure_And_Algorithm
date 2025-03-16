#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj; // Adjacency list: {neighbor, weight}

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V + 1);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Undirected Graph
    }

    void dijkstra(int src, int dest) {
        vector<int> dist(V + 1, numeric_limits<int>::max()); // Distance array
        vector<int> parent(V + 1, -1); // To store path
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (currDist > dist[node]) continue; // Skip outdated entries

            for (auto [neighbor, weight] : adj[node]) {
                int newDist = dist[node] + weight;
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    parent[neighbor] = node;
                    pq.push({newDist, neighbor});
                }
            }
        }

        // Print shortest distance
        if (dist[dest] == numeric_limits<int>::max()) {
            cout << "No path exists between " << src << " and " << dest << endl;
            return;
        }

        cout << "Shortest Distance from " << src << " to " << dest << ": " << dist[dest] << endl;

        // Print shortest path
        cout << "Shortest Path: ";
        stack<int> path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push(v);
        }

        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    Graph g(V);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int src, dest;
    cout << "Enter source and destination vertices: ";
    cin >> src >> dest;

    g.dijkstra(src, dest);

    return 0;
}
