// time O(N*W)
// space O(N+W) for dp + O(N) for recursion stack
# include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
const int maxW = 1e2;
const long long int inf = 1e15;

int weight[N+5];
long long int value[N+5];
long long int dp[N+5][maxW+5];

long long int calc(int n, int taken){
    if(n == 0){
        if(taken == 0) return 0;
        else return -inf;
    }
    if(dp[n][taken] != -1) return dp[n][taken];

    dp[n][taken] = calc(n-1, taken);     // not taking nth item
    if(taken >= weight[n]) dp[n][taken] = max(dp[n][taken], calc(n-1, taken-weight[n]) + value[n]);

    return dp[n][taken];
}
int main(){
    memset(dp, -1, sizeof(dp));
    int n, W;
    cin>>n>>W;
    for(int i= 1; i<=n; i++) cin>>weight[i]>>value[i];

    long long int ans = -inf;
    for(int w = 0; w <= W; w++){
        ans = max(ans, calc(n, w));
    }

    cout<<ans<<endl;
    return 0;
}




