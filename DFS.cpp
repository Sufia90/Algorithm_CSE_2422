include <iostream>
#include <vector>
using namespace std;

void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited) {

    visited[node] = true;
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

int main() {

    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> adj(n);

    for (int i = 0; i < e; i++) {
        int u, v;
        cout << "Enter edge (u v): ";
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    vector<bool> visited(n, false);

    cout << "DFS traversal: ";
    dfs(start, adj, visited);

    return 0;
}

