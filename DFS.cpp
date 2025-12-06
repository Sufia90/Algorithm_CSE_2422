#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfs(int node) {
    visited[node] = true;
    cout << node << " ";

    for (int nbr : graph[node]) {
        if (!visited[nbr]) dfs(nbr);
    }
}

int main() {
    int n, e;
    cin >> n >> e;

    graph.resize(n);
    visited.assign(n, false);

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cin >> start;

    dfs(start);
}
