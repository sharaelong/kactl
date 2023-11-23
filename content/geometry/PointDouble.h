/**
 * Author:
 * Description:
 */
#pragma once

int sgn(ld x) {
    return abs(x) < 1e-16L ? 0 : (x > 0 ? 1 : -1);
}

struct Point {
    ld x, y;
    Point operator-(const Point& r) const { return Point{ x-r.x, y-r.y }; }
    Point operator*(ld a) const { return Point{ x*a, y*a }; }
    ld operator*(const Point& r) const { return x * r.x + y * r.y; }
    ld operator^(const Point& r) const { return x * r.y - y * r.x; }
    bool operator<(const Point& r) const { return (sgn(x-r.x) < 0 || (sgn(x-r.x) == 0 && sgn(y-r.y) < 0)); }
    bool operator==(const Point& r) const { return (sgn(x-r.x) == 0 && sgn(y-r.y) == 0); }
    ld norm() const { return sqrtl(x*x + y*y); }
    ld sqnorm() const { return x*x + y*y; }
    friend istream& operator>>(istream& is, Point& p) { is >> p.x >> p.y; return is; }
    friend ostream& operator<<(ostream& os, const Point& p) { os << '(' << p.x << ' ' << p.y << ')'; return os; }
};
