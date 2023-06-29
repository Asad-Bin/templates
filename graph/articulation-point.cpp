const int N = 2e5;
int tin[N+5], low[N+5];
bool vis[N+5];
vector<int> art_point, edge[N+5];

int timer = 0;
void dfs(int u, int p = -1){
	tin[u] = low[u] = timer++;
	vis[u] = 1;
	
	int child = 0;
	for(int to : edge[u]){
		if(to == p) continue;
		
		if(vis[to]){
			low[u] = min(low[u], tin[to]);
		}
		else{
			dfs(to, u);
			
			low[u] = min(low[u], low[to]);
			if(low[to] >= tin[u] && p != -1){
				art_point.push_back(u);
			}
			++child;
		}
	}
	if(p == -1 && child >= 2){
		art_point.push_back(u);
	}
}
void cut_point(int n)
{
	timer = 0;
	art_point.clear();
	for(int K = 1; K <= n; K++) vis[K] = 0;
	
	for(int K = 1; K <= n; K++){
		if(!vis[K]){
			dfs(K);
		}
	}
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
