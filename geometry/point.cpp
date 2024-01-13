// . . . Bismillahir Rahmanir Rahim . . .


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
// typedef long long T;
typedef double T;
// by default it is double type, use 'long long' whenever possible.

template <typename T> int sign(T x) {
    return (T(0) < x) - (x < T(0));
}
struct pt {
    T x, y;

    pt() { x = 0, y = 0; }
    pt(T _x, T _y) : x(_x), y(_y) {}
    pt(const pt &p) : x(p.x), y(p.y)    {}

    pt operator + (const pt &a) const { return pt(x + a.x, y + a.y); }
    pt operator - (const pt &a) const { return pt(x - a.x, y - a.y); }
    pt operator * (const T a) const { return pt(x * a, y * a); } // scalar multiplication of vector
    // pt operator * (const double &a, const pt &b) { return pt(a * b.x, a * b.y); }
    pt operator / (const T a) const { return pt(x / a, y / a); } // scalar division of vector
    
    // use it to sort points based on co-ordinates
    bool operator < (pt a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    // bool operator > (pt a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }

    // for double numbers, for integers it's easier.
    bool operator == (pt a) const {return (fabs(x-a.x) < eps) && (fabs(y-a.y) < eps); }

    T sq() {return x*x + y*y;}

    pt perp() {return {-y, x};} // rotating by 90*, perpandicular

    pt truncate(double r) { // returns a vector with len r and having same direction
        double k = sq();
        if (!sign(k)) return *this;
        r /= k;
        return pt(x * r, y * r);
    }

    double dist(pt a, pt b){ return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); }
};
ostream& operator<<(ostream& os, pt p){
    return os << "(" << p.x << ", " << p.y << ")";
}

// for integer numbers
bool operator==(pt a, pt b) {return a.x == b.x && a.y == b.y;}
bool operator!=(pt a, pt b) {return !(a == b);}

double abs(pt p){return sqrt(p.sq()); }

pt translate(pt u, pt v) {return u+v; }
pt scale(pt c, double factor, pt p) { return c + (p-c)*factor; } // scaling a vector
pt rotateccw90(pt a) { return pt(-a.y, a.x); }
pt rotatecw90(pt a) { return pt(a.y, -a.x); }
pt rotateccw(pt a, double t) { return pt(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
pt rotatecw(pt a, double t) { return pt(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }

inline T dot(pt a, pt b) { return a.x * b.x + a.y * b.y; } // dot product
bool isPerp(pt a, pt b) {return dot(a, b) == 0; }
double angle(pt a, pt b) { // gives output angle of slope, [0, pi] for input [-1, 1];
    double costheta = dot(a, b) / abs(a) / abs(b);
    return acos(max((double)-1.0, min((double)1.0, costheta)));
}

// signed version, pos for ccw from a to b
inline T cross(pt a, pt b) { return a.x * b.y - a.y * b.x; } 
// returns direction of rotation from b to c wrt a. > 0 for ccw
inline T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
// check if p point is inside <abc. 
bool inAngle(pt a, pt b, pt c, pt p){
    assert(orient(a, b, c) != 0);
    if(orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}
double orientedAngle(pt a, pt b, pt c){ // output angle around a, from b to c, [0, 2*pi].
    if(orient(a, b, c) >= 0) return angle(b-a, c-a);
    else return 2*PI - angle(b-a, c-a);
}

bool half(pt p) { return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0); }
void polar_sort(vector<pt> &v) { // sort points in counterclockwise
    sort(v.begin(), v.end(), [](pt a,pt b) {
        return make_tuple(half(a), 0.0, a.sq()) < make_tuple(half(b), cross(a, b), b.sq());
    });
}
pt linearTransform(pt p, pt q, pt r, pt fp, pt fq) {
    pt pq = q-p, num{cross(pq, fq-fp), dot(pq, fq-fp)};
    return fp + pt{cross(r-p, num), dot(r-p, num)} / pq.sq();
}

struct line {
    pt a, b; // goes through points a and b
    pt v; T c;  //line form: direction vec [cross] (x, y) = c 
    line() {}
    //direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
        auto p = get_points();
        a = p.first; b = p.second;
    }

    // equation ax + by + c = 0
    line(T _a, T _b, T _c) : v({_b, -_a}), c(-_c) {
        auto p = get_points();
        a = p.first; b = p.second;
    }
    // goes through points p and q
    line(pt p, pt q) : v(q - p), c(cross(v, p)), a(p), b(q) {}

    pair<pt, pt> get_points() { //extract any two points from this line
        pt p, q; double a = -v.y, b = v.x; // ax + by = -c
        if (sign(a) == 0) {
            p = pt(0, -c / b);
            q = pt(1, -c / b);
        }
        else if (sign(b) == 0) {
            p = pt(-c / a, 0);
            q = pt(-c / a, 1);
        }
        else {
            p = pt(0, -c / b);
            q = pt(1, (-c - a) / b);
        }
        return {p, q};
    }
    //ax + by + c = 0
    array<T, 3> get_abc() {
        T a = -v.y, b = v.x;
        return {a, b, c};
    }
    // 1 if on the left, -1 if on the right, 0 if on the line
    int side(pt p) { return sign(cross(v, p) - c); }
    double dist(pt p){return abs(side(p)) / abs(v); }
    double sqdist(pt p){ return side(p)*side(p) / (double)v.sq(); }
    // line that is perpendicular to this and goes through point p
    line perpendicular_through(pt p) { return {p, p + v.perp()}; }
    // translate the line by vector t i.e. shifting it by vector t
    line translate(pt t) { return {v, c + cross(v, t)}; }
    // compare two points by their orthogonal projection on this line
    // a projection point comes before another if it comes first according to vector v
    // finding out who comes first
    bool cmp_by_projection(pt p, pt q) { return dot(v, p) < dot(v, q); }
    line shift_left(double d) {
        pt z = v.perp().truncate(d);
        return line(a + z, b + z);
    }
    pt proj(pt p) { return p - v.perp()*side(p)/v.sq();}
    pt refl(pt p) {return p - v.perp()*2*side(p)/v.sq();}
};

// intersection point, between ab and cd assuming unique intersection exists
bool line_line_intersection(pt a, pt b, pt c, pt d, pt &ans) {
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = pt((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}
// finds bisector line
// pt bisector(line l1, line l2, bool interior) {
//     assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
//     T sign = interior ? 1 : -1;
//     return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
//     l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
// }
// returns true if  point p is on line segment ab
bool is_point_on_seg(pt a, pt b, pt p) {
    if (fabs(cross(p - b, a - b)) < eps) {
        if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return false;
        if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
        return true;
    }
    return false;
}
// To create sets of points we need a comparison function
struct cmpX {
    bool operator()(pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};
set<pt,cmpX> inters(pt a, pt b, pt c, pt d) {
    pt out;
    if (line_line_intersection(a,b,c,d,out)) return {out};
    set<pt,cmpX> s;
    if (is_point_on_seg(c,d,a)) s.insert(a);
    if (is_point_on_seg(c,d,b)) s.insert(b);
    if (is_point_on_seg(a,b,c)) s.insert(c);
    if (is_point_on_seg(a,b,d)) s.insert(d);
    return s;
}
// minimum distance from point p to line through a and b
double min_dist_from_point_to_segment(pt a, pt b, pt p) {
    if (a != b) {
        line l(a,b);
        if (l.cmp_by_projection(a,p) && l.cmp_by_projection(p,b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}
// distance betn line (a, b) to line (c, d);
double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (line_line_intersection(a,b,c,d,dummy)) return 0;
    return min({min_dist_from_point_to_segment(a,b,c), 
        min_dist_from_point_to_segment(a,b,d), min_dist_from_point_to_segment(c,d,a), 
        min_dist_from_point_to_segment(c,d,b)});
}


/*
// find a point from a through b with distance d
pt point_along_line(pt a, pt b, double d) {
    return a + (((b - a) / (b - a).norm()) * d);
}
// projection point c onto line through a and b  assuming a != b
pt project_from_point_to_line(pt a, pt b, pt c) {
    return a + (b - a) * dot(c - a, b - a) / (b - a).norm2();
}
// reflection point c onto line through a and b  assuming a != b
pt reflection_from_point_to_line(pt a, pt b, pt c) {
    pt p = project_from_point_to_line(a,b,c);
    return point_along_line(c, p, 2.0 * dist(c, p));
}
// // minimum distance from point c to line through a and b
// double dist_from_point_to_line(pt a, pt b, pt c) {
//     return fabs(cross(b - a, c - a) / (b - a).norm());
// }
// // minimum distance point from point c to segment ab that lies on segment ab
// pt project_from_point_to_seg(pt a, pt b, pt c) {
//     double r = dist2(a, b);
//     if (fabs(r) < eps) return a;
//     r = dot(c - a, b - a) / r;
//     if (r < 0) return a;
//     if (r > 1) return b;
//     return a + (b - a) * r;
// }
// // minimum distance from point c to segment ab
// double dist_from_point_to_seg(pt a, pt b, pt c) {
//     return dist(c, project_from_point_to_seg(a, b, c));
// }
// 0 if not parallel, 1 if parallel, 2 if collinear
bool is_parallel(pt a, pt b, pt c, pt d) {
    double k = fabs(cross(b - a, d - c));
    if (k < eps){
        if (fabs(cross(a - b, a - c)) < eps && fabs(cross(c - d, c - a)) < eps) return 2;
        else return 1;
    }
    else return 0;
}
// check if two lines are same
bool are_lines_same(pt a, pt b, pt c, pt d) {
    if (fabs(cross(a - c, c - d)) < eps && fabs(cross(b - c, c - d)) < eps) return true;
    return false;
}
// bisector vector of <abc
pt angle_bisector(pt &a, pt &b, pt &c){
    pt p = a - b, q = c - b;
    return p + q * sqrt(dot(p, p) / dot(q, q));
}
// 1 if point is ccw to the line, 2 if point is cw to the line, 3 if point is on the line
int point_line_relation(pt a, pt b, pt p) {
    int c = sign(cross(p - a, b - a));
    if (c < 0) return 1;
    if (c > 0) return 2;
    return 3;
}
// intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(pt a, pt b, pt c, pt d, pt &ans) {
    double oa = cross2(c, d, a), ob = cross2(c, d, b);
    double oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0){
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}
// intersection point between segment ab and segment cd assuming unique intersection may not exists
// se.size()==0 means no intersection
// se.size()==1 means one intersection
// se.size()==2 means range intersection
set<pt> seg_seg_intersection_inside(pt a,  pt b,  pt c,  pt d) {
    pt ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<pt> se;
    if (is_point_on_seg(c, d, a)) se.insert(a);
    if (is_point_on_seg(c, d, b)) se.insert(b);
    if (is_point_on_seg(a, b, c)) se.insert(c);
    if (is_point_on_seg(a, b, d)) se.insert(d);
    return se;
}
// intersection  between segment ab and line cd
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect
int seg_line_relation(pt a, pt b, pt c, pt d) {
    double p = cross2(c, d, a);
    double q = cross2(c, d, b);
    if (sign(p) == 0 && sign(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}
// intersection between segament ab and line cd assuming unique intersection exists
bool seg_line_intersection(pt a, pt b, pt c, pt d, pt &ans) {
    bool k = seg_line_relation(a, b, c, d);
    assert(k != 2);
    if (k) line_line_intersection(a, b, c, d, ans);
    return k;
}
// minimum distance from segment ab to segment cd
double dist_from_seg_to_seg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (seg_seg_intersection(a, b, c, d, dummy)) return 0.0;
    else return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d), 
        dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
// minimum distance from point c to ray (starting point a and direction vector b)
double dist_from_point_to_ray(pt a, pt b, pt c) {
    b = a + b;
    double r = dot(c - a, b - a);
    if (r < 0.0) return dist(c, a);
    return dist_from_point_to_line(a, b, c);
}
// starting point as and direction vector ad
bool ray_ray_intersection(pt as, pt ad, pt bs, pt bd) {
    double dx = bs.x - as.x, dy = bs.y - as.y;
    double det = bd.x * ad.y - bd.y * ad.x;
    if (fabs(det) < eps) return 0;
    double u = (dy * bd.x - dx * bd.y) / det;
    double v = (dy * ad.x - dx * ad.y) / det;
    if (sign(u) >= 0 && sign(v) >= 0) return 1;
    else return 0;
}
double ray_ray_distan e(pt as, pt ad, pt bs, pt bd) {
    if (ray_ray_intersection(as, ad, bs, bd)) return 0.0;
    double ans = dist_from_point_to_ray(as, ad, bs);
    ans = min(ans, dist_from_point_to_ray(bs, bd, as));
    return ans;
}
*/


double area_of_triangle(pt a, pt b, pt c){
    return abs(cross(b-a, c-a))*0.5;
}
double area_of_polygon(vector<pt> &v){
    T area = 0;
    for(int K = 0, n = (int)v.size(); K < n; K++){
        area += cross(v[K], v[(K+1)%n]);
    }
    return abs(area)*0.5;
}
bool cmp(const pt &l, const pt &r) { return l.x < r.x || (l.x == r.x && l.y < r.y); }
bool pointInTriangle(pt a, pt b, pt c, pt point) {
    long long s1 = abs(orient(a, b, c));
    long long s2 = abs(orient(point, a, b)) + abs(orient(point, b, c)) + abs(orient(point, c, a));
    return s1 == s2;
}
pt translation;
vector<pt> seq;
void prepare(vector<pt> &points) {
    int n = points.size();
    int pos = 0;
    for (int i = 1; i < n; i++) {
            if (cmp(points[i], points[pos])) pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());
    n--;

    seq.resize(n);
    for (int i = 0; i < n; i++) seq[i] = points[i + 1] - points[0];
    translation = points[0];
}
bool point_in_convex_polygon(vector<pt> &seq, pt point) {
    int n = (int)seq.size();

    point = point - translation;
    if (cross(seq[0], point) != 1 && sign(cross(seq[0], point)) != sign(cross(seq[0], seq[n - 1]))) return false;
    if (cross(seq[n - 1], point) != 0 && sign(cross(seq[n - 1], point)) != sign(cross(seq[n - 1], seq[0]))) return false;
    if (cross(seq[0], point) == 0) return abs(seq[0]) >= abs(point);
    int l = 0, r = n - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        int pos = mid;
        if (cross(seq[pos], point) >= 0)
                l = mid;
        else
                r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], pt(0, 0), point);
}
bool above(pt a, pt p) {
    return p.y >= a.y;
}
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
    return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}
bool point_in_polygon(vector<pt> &a, pt p, bool strict = true){
    int numCrossings = 0;
    for(int K = 0, n = (int)a.size(); K < n; K++){
        if(is_point_on_seg(a[K], a[(K+1)%n], p)){
            return strict;
        }
        numCrossings += crossesRay(p, a[K], a[(K+1)%n]);
    }
    return numCrossings&1;
}
// amplitude travelled around point A, from P to Q, [-pi, pi]
double angleTravelled(pt a, pt p, pt q) {
    double ampli = angle(p-a, q-a);
    if (orient(a,p,q) > 0) return ampli;
    else return -ampli;
}
int windingNumber(vector<pt> p, pt a) {
    double ampli = 0;
    for (int i = 0, n = p.size(); i < n; i++)
    ampli += angleTravelled(a, p[i], p[(i+1)%n]);
    return round(ampli / (2*PI));
}

// struct angle { // [-pi+2*pi*t, pi+2*pi*t]
//     pt d; int t = 0; // direction and number of full turns
//     angle t180(); // to be defined later
//     angle t360() {return {d, t+1};}
// };


/// circle region
// a circle around a triangle {a, b, c}
pt circum_circle(pt a, pt b, pt c){ // check for 'double' value of pt.
    b = b-a, c = c-a;
    assert(cross(b, c) != 0);
    return a+ (b*c.sq() - c*b.sq()).perp()/cross(b, c)/2;
}
// 0 for not intersect, 1 for tangent, 2 for intersection
int circle_line_intersect(pt o, double r, line l, pair<pt,pt> &out) {
    double h2 = r*r - l.sqdist(o);
    if (h2 >= 0) { // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v*sqrt(h2)/abs(l.v); // vector parallel to l, of length h
        out = {p-h, p+h};
    }
    return 1 + sign(h2);
}
int circle_circle_intersect(pt o1, double r1, pt o2, double r2, pair<pt,pt> &out) {
    pt d=o2-o1; double d2=d.sq();
    if (d2 == 0) {assert(r1 != r2); return 0;} // concentric circles 
    double pd = (d2 + r1*r1 - r2*r2)/2; // = |O_1P| * d
    double h2 = r1*r1 - pd*pd/d2; // = hˆ2
    if (h2 >= 0) {
        pt p = o1 + d*pd/d2, h = d.perp()*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sign(h2);
}
// finds outer tangents of 2 circles;
// -1 for infinite tangets, circles are same
// for circle tangent to each other from inside, returns 'out' with 4 equal point value
// same code can be used to find tangent from a point to a circle, with 2nd circle radius 0.
int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt,pt>> &out) {
    if (inner) r2 = -r2;
    pt d = o2-o1;
    double dr = r1-r2, d2 = d.sq(), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) { return -1;}
    for (int sign : {-1,1}) {
        pt v = (d*dr + d.perp()*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1; //cin >> t;
    for(int cs = 1; cs <= t; cs++){
        // cout << "Case " << cs << ": ";

        // vector<pair<pt, pt> > out;

        // int ans = tangents(pt(0, 0), 5, pt(0, 0), 3, false, out);

        // cout << ans << "\n";
        // for(auto it: out){
        //     cout << it.first.x << ' ' << it.first.y << ", " << it.second.x << ' ' << it.second.y << "\n";
        // }
    }

    return 0;
}





























