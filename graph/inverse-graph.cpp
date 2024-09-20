const int N = 2e5;
vector<int> g[N+5], par(N+5), vis(N+5, 0);

int Find(int x)
{
	return par[x] == x ? x : par[x] = Find(par[x]);
}
void dfs(int u, int n)
{
	if(vis[u]) return;
	
	vis[u] = 1;
	par[u] = Find(u+1);
	
	int v = 0;
	for(auto it: g[u]){
		v = Find(v+1);
		while(v < it){
			dfs(v, n);
			v = Find(v+1);
		}
		v = it;
	}
	v = Find(v+1);
	while(v <= n){
		dfs(v, n);
		v = Find(v+1);
	}
}
ininialize with:
for(int K = 1; K <= n+1; K++) par[K] = K; // n+1 is important
for(int K = 1; K <= n; K++) vis[K] = 0;
call with: 
for(int K = 1; K <= n; K++) if(!vis[K]){
	dfs(K, n);
}
