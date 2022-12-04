struct point {
    long long x;
    long long y;
    // may need 'double' type variable
    point() {}
    point(long long _x, long long _y) {
            x = _x;
            y = _y;
    }
};
// Input: a sorted(inti-clockwise) vector
// Output: area of polygon
// Need a counter-clockwise sorted vector
// To sort, we have to just divide them in up points
// and down points after sorting them lexicographically
double poly_area(int n, vector<point>& v) {
    // We can use 'long long' instead of 'double' to lessen
    precision error
        // and divide the answer by 2 later on.
        double res = 0;
    for (int K = 0; K < n; K++) {
            point a = (K ? v[K - 1] : v[n - 1]);
            point b = v[K];
            res = (a.x - b.x) * (a.y + b.y);
    }
    return res / 2.0;
}
// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {
    double result = 0.0;
    for (int i = 0; i < (int)P.size() - 1; i++)  // remember that P[0] = P[n-1]
            result += dist(P[i], P[i + 1]);
    return result;
}

bool cmp(point a, point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool cw(point a, point b, point c) { return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0; }
bool ccw(point a, point b, point c) { return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0; }

// Checking if a polygon in convex
bool isConvex(const vector<point> &P) {                                                 // returns true if all three
    int sz = (int)P.size();                                                             // consecutive vertices of P form the same turns
    if (sz <= 3) return false;                                                          // a point/sz=2 or a line/sz=3 is not convex
    bool isLeft = ccw(P[0], P[1], P[2]);                                                // remember one result
    for (int i = 1; i < sz - 1; i++)                                                    // then compare with the others
        if (ccw(P[i], P[i + 1], P[(i + 2) == sz ? 1 : i + 2]) != isLeft) return false;  // different sign -> this polygon is concave
    return true;'area of polygon.cpp'
}


// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
    if ((int)P.size() == 0) return false;
    double sum = 0;  // assume the first vertex is equal to the last vertex
    for (int i = 0; i < (int)P.size() - 1; i++) {
        if (ccw(pt, P[i], P[i + 1]))
            sum += angle(P[i], pt, P[i + 1]);  // left turn/ccw
        else
            sum -= angle(P[i], pt, P[i + 1]);
    }  // right turn/cw
    return fabs(fabs(sum) - 2 * PI) < EPS;
}

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}
// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
    vector<point> P;
    for (int i = 0; i < (int)Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
        if (i != (int)Q.size() - 1) left2 = cross(toVec(a, b), toVec(a, Q[i + 1]));
        if (left1 > -EPS) P.push_back(Q[i]);  // Q[i] is on the left of ab
        if (left1 * left2 < -EPS)             // edge (Q[i], Q[i+1]) crosses line ab
            P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front())) P.push_back(P.front());  // make P's first point = P's last point
    return P;
}
