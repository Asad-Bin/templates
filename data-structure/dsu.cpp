// code 1
const int N = 2e5;
int dsu[N+5], sz[N+5];
// sz[] is initialized by value 1;
// dsu[] if initialized by dsu[K] = K

int Find(int x)
{
    if(dsu[x] == x) return dsu[x];
    return dsu[x] = Find(dsu[x]);
}
void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    
    if(a != b){
        if(sz[a] > sz[b]) swap(a, b);
        
        dsu[a] = b;
        sz[b] += sz[a];
    }
}


// code 2
void init(int N) {
    for (int i = 0; i < N; ++i) {
        pre[i] = i;
        height[i] = 0;
    }
}

int find(int node) {
    if (pre[node] != node) {
            pre[node] = find(pre[node]);
    }
    return pre[node];
}

void unite(int A, int B) {
    A = find(A);
    B = find(B);
    if (A == B) return;
    if (height[A] > height[B]) {
        pre[B] = A;
        height[A] = max(height[A], height[B] + 1);
    } else {
        pre[A] = B;
        height[B] = max(height[B], height[A] + 1);
    }
}

Smaller to larger (DSU on tree)
Trees are a very special kind of graph and many procedures on trees can be optimized. One of these optimizations is called “Smaller to Larger”, also known as “Dsu on Trees”.A way to merge two sets efficiently.
let's prove that there's at most O(N log N) moves, each move can be done in O(log N) so total complexity is O(N log^2 N)
when you are merging two sets you move elements from smaller set(assume its size is K) to bigger one, so every element in the smaller set now is in a set with at least size 2K
In other words every element that has been moved T times is in a set with at least size 2^T , thus every element will be moved at most O(log N) and we have N elements so in total there will be at most O(N log N) move operations.
Here ,duplicate values aren’t considered because we are assuming the worst case scenario.If we found any duplicate value then that node will not be counted in further operation.So, duplicate values will reduce complexity.
Complexity : O(nlog2n)

