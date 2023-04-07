#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, adj_rev;
vector<bool> used;
vector<int> order, component;

void dfs1(int u) {
    used[u] = true;
    
    for (auto v : adj[u])
        if (!used[v])
            dfs1(v);

    order.push_back(u);
}

void dfs2(int u) {
    used[u] = true;
    component.push_back(u);

    for (auto v : adj_rev[u])
        if (!used[v])
            dfs2(v);
}

int main() {
    int n;
    // ... read n ...

    for (;;) {
        int a, b; cin >> a >> b;
        
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }

    used.assign(n, false);

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    used.assign(n, false);
    reverse(order.begin(), order.end());

    for (auto v : order)
        if (!used[v]) {
            dfs2 (v);

            // ... processing next component ...

            component.clear();
        }
}

/// Condensation Graph Implementation
vector<int> roots(n, 0);
vector<int> root_nodes;
vector<vector<int>> adj_scc(n);

//for (auto v : order)
    //if (!used[v]) {
        //dfs2(v);

        int root = component.front();
        for (auto u : component) roots[u] = root;
        root_nodes.push_back(root);

        //component.clear();
    //}


for (int v = 0; v < n; v++){
    for (auto u : adj[v]) {
        int root_v = roots[v],
            root_u = roots[u];

        if (root_u != root_v)
            adj_scc[root_v].push_back(root_u);
    }
}
