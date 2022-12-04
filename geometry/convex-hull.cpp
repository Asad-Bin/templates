// complexity O(n*logn)
// input: set of 2D points
// output: convex hull with sorted counter-clockwise

bool cmp(point a, point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool cw(point a, point b, point c) { return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0; }
bool ccw(point a, point b, point c) { return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0; }

void convex_hull(int n, vector<point>& v) {
    if (n == 1) return;
    sort(all(v), &cmp);
    if (v[0].x == v[n - 1].x && v[0].y == v[n - 1].y) {
            point a = v[0];
            v.clear();
            v.PB(a);
            return;
    }
    point p1 = v[0], p2 = v[n - 1];
    vector<point> up, down;
    up.PB(p1);
    down.PB(p1);
    for (int K = 1; K < n; K++) {
            if (K == n - 1 || cw(p1, v[K], p2)) {
              // while(sz(up)>=2 && !cw(up[sz(up)-2], up[sz(up)-1], v[K]))
             // up.pop_back();
             up.PB(v[K]);
               }
            if (K == n - 1 || ccw(p1, v[K], p2)) {
             // while(sz(down)>=2 && !ccw(down[sz(down)-2],down[sz(down)-1], v[K]))
             // down.pop_back();
             down.PB(v[K]);
            }
    }
    v.clear();
    for (int K = 0; K < sz(down); K++) v.PB(down[K]);
    for (int K = sz(up) - 2; K > 0; K--) v.PB(up[K]);
}
// from CP3
point pivot(0, 0);
bool angleCmp(point a, point b) {                // angle-sorting function
    if (collinear(pivot, a, b))                  // special case
        return dist(pivot, a) < dist(pivot, b);  // check which one is closer
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}  // compare two angles
vector<point> CH(vector<point> P) {  // the content of P may be reshuffled
    int i, j, n = (int)P.size();
    if (n <= 3) {
            if (!(P[0] == P[n - 1])) P.push_back(P[0]);  // safeguard from corner case
            return P;
    }  // special case, the CH is P itself
    // first, find P0 = point with lowest Y and if tie: rightmost X
    int P0 = 0;
    for (i = 1; i < n; i++)
             if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x)) P0 = i;
    point temp = P[0];
    P[0] = P[P0];
    P[P0] = temp;  // swap P[P0] with P[0]
    // second, sort points by angle w.r.t. pivot P0
    pivot = P[0];                          // use this global variable as reference
    sort(++P.begin(), P.end(), angleCmp);  // we do not sort P[0]
    // third, the ccw tests
    vector<point> S;
    S.push_back(P[n - 1]);
    S.push_back(P[0]);
    S.push_back(P[1]);  // initial S
    i = 2;              // then, we check the rest
    while (i < n) {     // note: N must be >= 3 for this method to work
            j = (int)S.size() - 1;
            if (ccw(S[j - 1], S[j], P[i]))
             S.push_back(P[i++]);  // left turn, accept
            else
             S.pop_back();
    }  // or pop the top of S until we have a left turn
    return S;
}

