/**
 * Author:
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * Status: not tested.
 */
#pragma once

// True when p is endpoint
bool onSegment(Point s, Point e, Point p) {
  return ((s-p) ^ (e-p)) == 0 && (s - p) * (e - p) <= 0;
}

bool inPolygon(vector<Point> &p, Point a, bool strict = true) {
  int cnt = 0, n = sz(p);
  rep(i,0,n) {
    Point q = p[(i + 1) % n];
    if (onSegment(p[i], q, a)) return !strict;
    //or: if (segDist(p[i], q, a) <= eps) return !strict;
    cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * ((p[i]-a) ^ (q-a)) > 0;
  }
  return cnt;
}
