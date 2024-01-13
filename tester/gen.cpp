#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// int mrand(int a, int b)
// {
// 	return a+rand()%(b-a+1);
// }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll  mrand(ll l, ll r) {
    return uniform_int_distribution<ll>(l,r) (rng);
}
int main(int argc, char* argv[])
{
	srand(atoi(argv[1]));
	
	int t = mrand(1, 10);
	cout << t << "\n";
	
	while(t--){
		ll a = mrand(1, 1000000);
		ll b = mrand(1, 1000000);
		ll c = mrand(1, 1000000);

		cout << a << ' ' << b << ' ' << c << "\n";
		
		
		// ll l = mrand(1, n*(n-1)+1);
		// ll r = mrand(l, n*(n-1)+1);
		
		// cout << n << ' ' << l << ' ' << r << "\n";
	}
	
	// cout << 10000<< "\n";
	// for(int K = 1; K <= 10000; K++) cout << mrand(10000000, 1000000000) << ' ' << 10 << "\n";
}













































