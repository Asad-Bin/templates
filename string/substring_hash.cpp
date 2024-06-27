const int N = 3e5;
const ll b1 = 29;
const ll b2 = 31;
const ll mod1 = 1e9+7;
const ll mod2 = 1e9+9;

string s;
ll hash1[N+5], hash2[N+5], pow1[N+5], pow2[N+5];
void pre_calc()
{
	pow1[0] = pow2[0] = 1;
	for(int K = 1; K < N; K++){
		pow1[K] = pow1[K-1]*b1%mod1;
		pow2[K] = pow2[K-1]*b2%mod2;
	}
}
void build_hash(string &s, int n)
{
	hash1[0] = hash2[0] = s[0]-'a'+1;
	for(int K = 1; K < n; K++){
		hash1[K] = (hash1[K-1] + ((s[K]-'a'+1)*pow1[K]%mod1)) % mod1;
		hash2[K] = (hash2[K-1] + ((s[K]-'a'+1)*pow2[K]%mod2)) % mod2;
	}
}
// hash of substring s[i....j].
pair<ll, ll> substring(int i, int j)
{
	if(i > j) return {-1, -1}; // returns impossible

	ll a = hash1[j] - (i ? hash1[i-1] : 0);
	ll b = hash2[j] - (i ? hash2[i-1] : 0);

	a %= mod1;
	b %= mod2;
	a = (a+mod1)%mod1;
	b = (b+mod2)%mod2;

	a = a * inverse_mod(pow1[i], mod1) % mod1;
	b = b * inverse_mod(pow2[i], mod2) % mod2;

	return {a, b};
}