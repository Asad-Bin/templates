namespace path_copying_segree {
	int L[N * LOGN], R[N * LOGN], ST[N * LOGN], blen, root[N];
	// sparse persistent-segtree. range sum, initially 0
	int update(int pos, int add, int l, int r, int id) {
		if (l > pos || r <= pos) return id;
		int ID = ++blen, m = l + (r - l) / 2;
		if (l == r - 1) return (ST[ID] = ST[id] + add, ID);
		L[ID] = update(pos, add, l, m, L[id]);
		R[ID] = update(pos, add, m, r, R[id]);
		return (ST[ID] = ST[L[ID]] + ST[R[ID]], ID);
	}
	void update(int A[], int n) {
		root[0] = ++blen;
		for (int i = 1; i <= n; i++) root[i] = update(A[i], 1, 1, MX, root[i - 1]);
	}
	int query(int qL, int qR, int l, int r, int x) {
		if (!x || r <= qL || qR <= l) return 0;
		if (l >= qL && r <= qR) return ST[x];
		int m = l + (r - l) / 2;
		return query(qL, qR, l, m, L[x]) + query(qL, qR, m, r, R[x]);
	}
	int query(int l, int r, int k) { 
		return query(k + 1, MX, 1, MX, root[r]) - query(k + 1, MX, 1, MX, root[l - 1]); 
	}
}  // namespace path_copying_segree


//code 2...
const int mx_q = 2e5;
const int N = 2e5;
int ara[N + 5];
struct node {
    int val;
    node *left, *right;
    node(int a = 0, node *b = NULL, node *c = NULL): val(a), left(b), right(c) {}
    void build(int l, int r) {
            if (l == r) { val = ara[l]; return; }
            left = new node();
            right = new node();

            int mid = (l + r) / 2;
            left->build(l, mid);
            right->build(mid + 1, r);
            val = left->val + right->val;
    }

    node *update(int l, int r, int idx, int v) {
            if (idx < l || r < idx) return this;
            if (l == r) {
               node *ret = new node(val, left, right);
              ret->val += v;
             return ret;
            }
            int mid = (l + r) / 2;
            node *ret = new node(val);
            ret->left = left->update(l, mid, idx, v);
            ret->right = right->update(mid + 1, r, idx, v);

            ret->val = ret->left->val + ret->right->val;
            return ret;
    }

    int query(int l, int r, int L, int R) {
            if (r < L || R < l) return 0;
            if (L <= l && r <= R) return val;
            int mid = (l + r) / 2;
            return left->query(l, mid, L, R) + right->query(mid + 1, r, L, R);
    }
} * root[mx_q + 5];

int main() {
    int n, idx, val;
    cin >> n;
    for (int K = 1; K <= n; K++) cin >> ara[K];

    root[0] = new node();
    root[0]->build(1, n);

    cin >> idx >> val;
    root[1] = root[0]->update(1, n, idx, val);  // for creating a new version of tree
    // root[0] = root[0] -> update(1, n, idx, val); // for updating a old version of tree

    cout << root[0]->query(1, n, 1, 5) << "\n";
    cout << root[0]->query(1, n, 5, 10) << "\n";
    cout << root[1]->query(1, n, 1, 5) << "\n";
    cout << root[1]->query(1, n, 5, 10) << "\n";
    return 0;
}
