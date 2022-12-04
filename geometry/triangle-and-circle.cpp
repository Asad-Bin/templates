double perimeterTriangle(double a, double b, double c) { return a + b + c; }
double areaTriangle(double a, double b, double c) { return sqrt(s * (s - a) * (s - b) * (s - c)); }
double rInCircle(double ab, double bc, double ca) {
    // radius of inscribed circle in a triangle
    return areaTriangle(ab, bc, ca) / (0.5 * perimeterTriangle(ab, bc, ca));
}
double rCircumCircle(double ab, double bc, double ca) { return ab * bc * ca / (4.0 * areaTriangle(ab, bc, ca)); }
double rCircumCircle(point a, point b, point c) { return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }
point cCircumCircle(point a, point b, point c) {
    b.x -= a.x;
    b.y -= a.y;
    c.x -= a.x;
    c.y -= a.y;
    double d = 2.0 * (b.x * c.y - b.y * c.x);
    double p = (c.y * (b.x * b.x + b.y * b.y) - b.y * (c.x * c.x + c.y * c.y)) / d;
    double q = (b.x * (c.x * c.x + c.y * c.y) - c.x * (b.x * b.x + b.y * b.y)) / d;
    return point(p + a.x, q + a.y);
}
