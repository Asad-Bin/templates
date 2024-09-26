for(int K = 0; K < (1<<N); K++) dp[K] = ara[K];
for(int K = 0; K < N; K++){
	for(int mask = 0; mask < (1<<N); mask++){
		if((mask&(1<<K)) == 0) dp[mask] += dp[mask^(1<<K)];
	}
}
