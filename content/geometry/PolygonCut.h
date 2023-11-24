/**
 * Author:
 * Description: Returns the polygon on the left of line l. 
 * Usage:
 * Status: not tested.
 */
#pragma once

// l = p + d*t, l.q() = l + d
// doubled_signed_area(p,q,r) = (q-p) ^ (r-p)
vector<Point> polygon_cut(const vector<Point> &a, const line<T> &l){
  vector<Point> res;
  for(auto i = 0; i < (int)a.size(); ++ i){
    auto cur = a[i], prev = i ? a[i - 1] : a.back();
    bool side = doubled_signed_area(l.p, l.q(), cur) > 0;
    if(side != (doubled_signed_area(l.p, l.q(), prev) > 0))
      res.push_back(l.p + ((cur - l.p) ^ (prev - cur)) / ((l.d ^ prev) - cur) * l.d); // line intersection
    if(side) res.push_back(cur);
  }
  return res;
}
