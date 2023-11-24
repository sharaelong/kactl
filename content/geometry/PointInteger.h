/**
 * Author:
 * Description:
 */
#pragma once

struct Point {
  ll x, y;
  Point operator-(const Point& r) const { return Point{ x-r.x, y-r.y }; }
  ll operator^(const Point& r) const { return x * r.y - y * r.x; }
  bool operator<(const Point& r) const { return (x == r.x ? y < r.y : x < r.x); }
  bool operator==(const Point& r) const { return (x == r.x && y == r.y); }
  friend istream& operator>>(istream& is, Point& p) { is >> p.x >> p.y; return is; }
  friend ostream& operator<<(ostream& os, const Point& p) { os << '(' << p.x << ' ' << p.y << ')'; return os; }
};
