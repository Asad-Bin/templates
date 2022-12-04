// Bismillahir Rahmanir Rahim.
// CUET_Phantom_Troupe

#include <bits/stdc++.h>
using namespace std;

// typedefs...
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;

// constants...
const ll EPS = 1e-9;

// defines...
#define boost_ ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define iter_(i, n) for (int i = 0; i < int(n); i++)
#define for_n(i, n) for (int i = 1; i <= int(n); i++)
#define print_arr(a) for (int i = 0; i < n; i++) cout << a[i] << " ";
#define rev(i, n) for (int i = n; i >= 0; i--)
#define itr ::iterator
#define s_sort(s) sort(s.begin(), s.end())
#define n_sort(a, n) sort(a, a + n)
#define precise_impact cout << setprecision(10) << fixed;
#define endl "\n"

// chess moves...
// int dx[] = {+0, +0, -1, +1}; ///Up-down, Left-Right
// int dy[] = {+1, -1, +0, +0};
// int dx[] = {+0,+0,+1,-1,-1,+1,-1,+1}; ///King's Move
// int dy[] = {-1,+1,+0,+0,+1,+1,-1,-1};
// int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2}; ///Knight'sMove
// int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// structs...
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

// functions...
ll gcd(ll a, ll b){ while (b){ a %= b; swap(a, b);} return a;}
ll lcm(ll a, ll b){ return (a/gcd(a, b)*b);}
ll ncr(ll a, ll b){ ll x = max(a-b, b), ans=1; for(ll K=a, L=1; K>=x+1; K--, L++){ ans = ans * K; ans /= L;} return ans;}
ll bigmod(ll a,ll b,ll mod){ if(b==0){ return 1;} ll tm=bigmod(a,b/2,mod); tm=(tm*tm)%mod; if(b%2==1) tm=(tm*a)%mod; return tm;}
ll egcd(ll a,ll b,ll &x,ll &y){ if(a==0){ x=0; y=1; return b;} ll x1,y1; ll d=egcd(b%a,a,x1,y1); x=y1-(b/a)*x1; y=x1; return d;}
ll modpow(ll a,ll p,ll mod) {ll ans=1;while(p){if(p%2)ans=(ans*a)%mod;a=(a*a)%mod;p/=2;} return ans;}
ll inverse_mod(ll n,ll mod) {return modpow(n,mod-2,mod);}

int main() {
    boost_;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // Code here. . . .
    return 0;
}

