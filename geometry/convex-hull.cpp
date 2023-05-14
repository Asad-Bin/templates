struct pt {
    double x, y;
};
 
int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}
 
bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o > 0 || (include_collinear && o == 0);
}
 
void convex_hull(vector<pt>& ara, bool include_collinear = false) {
    if (ara.size() == 1)
        return;
 
    sort(ara.begin(), ara.end(), [](pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    pt p1 = ara[0], p2 = ara.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)ara.size(); i++) {
        if (i == ara.size() - 1 || cw(p1, ara[i], p2, include_collinear)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], ara[i], include_collinear))
                up.pop_back();
            up.push_back(ara[i]);
        }
        if (i == ara.size() - 1 || ccw(p1, ara[i], p2, include_collinear)) {
            while (down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], ara[i], include_collinear))
                down.pop_back();
            down.push_back(ara[i]);
        }
    }
 
    if (include_collinear && up.size() == ara.size()) {
        reverse(ara.begin(), ara.end());
        return;
    }
    ara.clear();
    for (int i = 0; i < (int)up.size(); i++)
        ara.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        ara.push_back(down[i]);
}
