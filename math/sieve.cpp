// sieve :- prime number generator;
// 0 for prime, 1 for not prime;

const int N = 2e5;
vector<int> primes;
vector<bool> mark(1000002);
void sieve()
{
    mark[1] = 1;

    for(i = 4; i<=N; i+=2) mark[i] = 1;

    primes.push_back(2);

    for(ll i = 3; i <= n; i += 2)
    {
            if(!mark[i]){
                primes.push_back(i);
                for(ll j = i*i; j <= n; j += i*2) mark[j] = 1;
            }
    }
}
// Block/Segmented Sieve:
// Output: prime list in range {L, R}; (R-L+1) <= 1e7 && R <=  1e12;
vector<char> segmentedSieve(long long L, long long R) {  // generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
            if (!mark[i]) {
             primes.emplace_back(i);
             for (long long j = i * i; j <= lim; j += i) mark[j] = true;
            }
    }
    vector<char> isPrime(R - L + 1, true);
    for (long long i : primes)
            for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) isPrime[j - L] = false;
    if (L == 1) isPrime[0] = false;
    return isPrime;
}
// Bitwise - sieve :- prime number generator;
// 0 for prime, 1 for not prime; >> Not sure ... #define MX 10000000
int marked[MX / 64 + 2];
vector<int> primes;
#define mark(x) marked[x >> 6] |= (1 << ((x & 63) >> 1)) 
#define check(x)(marked[x >> 6] & (1 << ((x & 63) >> 1)))
bool isPrime(int x) { return (x > 1) && ((x == 2) || ((x & 1) && (!(check(x))))); }
void sieve(int n) {
    int i, j;
    primes.push_back(2);
    for (i = 3; i * i <= n; i += 2) {
            if (!check(i)) {
              primes.push_back(i);
             for (j = i * i; j <= n; j += i << 1) mark(j);
            }
    }
}

