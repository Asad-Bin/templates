const int N = 2e5;
int tin[N+5], low[N+5];
bool vis[N+5];
vector<int> edge[N+5];
vector<pair<int, int> > art_bridge;

int timer = 0;
void dfs(int u, int p = -1){
	tin[u] = low[u] = timer++;
	vis[u] = 1;
	
	for(int to : edge[u]){
		if(vis[to]){
			low[u] = min(low[u], tin[to]);
		}
		else{
			dfs(to, u);
			
			low[u] = min(low[u], low[to]);
			if(low[to] > tin[u]){
				art_bridge.push_back({u, to});
			}
		}
	}
}
void cut_bridge(int n)
{
	timer = 0;
	art_bridge.clear();
	for(int K = 1; K <= n; K++) vis[K] = 0;
	
	for(int K = 1; K <= n; K++){
		if(!vis[K]){
			dfs(K);
		}
	}
}
