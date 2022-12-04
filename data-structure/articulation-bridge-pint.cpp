void dfsCut(int par, int u) {
    low[u] = dfstime[u] = ++cnt;
    for (auto v : adj[u]) {
            if (dfstime[v] == 0) {
                  if (u == dfsroot) rc++;
                  dfsCut(u, v);
                  if (low[v] >= dfstime[u]) cutnode[u] = true;
                  if (low[v] > dfstime[u]) brdg.emplace_back(u, v);
                      low[u] = min(low[u], low[v]);
              } else if (v != par) {
                      low[u] = min(low[u], dfstime[v]);
              }
    }
}
int main() {
    cnt = 0;
    cutnode.assign(n + 2, 0);
    for (int i = 1; i <= n; i++) {
            if (dfstime[i] > 0) continue;
            dfsroot = i;
            rc = 0;
            dfsCut(-1, i);
            cutnode[dfsroot] = (rc > 1);
    }
}

