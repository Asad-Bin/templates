const int N = 1e5;
set<int> ara[N+5];
int cnt[N+5], par[N+5], ans[N+5];
 
/// Use LCA to get common anchestor node of two nodes.
/// LCA needs to be preprocessed before calling decompose(1, -1); function.
void dfs0(int u, int p)
{
    cnt[u] = 1;
 
    for(auto v: ara[u]){
        if(v != p){
            dfs0(v, u);
            cnt[u] += cnt[v];
        }
    }
}
int dfs1(int u, int p, int n)
{
    for(auto v: ara[u]){
        if(v != p && cnt[v] > n/2){
            // cout << u << ' ' << p << ' ' << v << ' '<< cnt[v] << "\n";
            return dfs1(v, u, n);
        }
    }
 
    return u;
}
void decompose(int root, int p, int n)
{
    dfs0(root, root);
    int centroid = dfs1(root, root, cnt[root]);
 
    if(p == -1) p = centroid;
    par[centroid] = p;

    for(auto v = ara[centroid].begin(); v != ara[centroid].end(); v++){
        ara[*v].erase(centroid);
        decompose(*v, centroid, n);
    }
    ara[centroid].clear();
}

// example update and query function...
int dist(int u, int v)
{
    return depth[u]+depth[v] - 2*depth[get_lca(u, v)];
}
void update(int u)
{
    int x = u;
 
    while(true){
        ans[x] = min(ans[x], dist(u, x));
        if(x == par[x]) break;
        x = par[x];
    }
}
int query(int u)
{
    int mn = inf;
    int x = u;
 
    while(true){
        mn = min(mn, dist(u, x)+ans[x]);
        if(x == par[x]) break;
        x = par[x];
    }
 
    return mn;
}