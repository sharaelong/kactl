/**
 * Author:
 * Description: Calculate intersection of left half plane of line (s->t).
 * Usage: 0-base index. vector<Point> ret = HPI(lines);
 * Time: O(N \log N), no data.
 */
#pragma once

struct Line { Point s, t; };
const ld eps = 1e-9;
bool equals(ld a, ld b) { return abs(a-b) < eps; }

bool line_intersect(Point& s1, Point& e1, Point& s2, Point& e2, Point& v) {
  ld det = (e2-s2) ^ (e1-s1);
  if (equals(det, 0)) return 0;
  ld s = (ld)((s2.x-s1.x) * (s2.y-e2.y) + (s2.y-s1.y) * (e2.x-s2.x)) / det;
  v.x = s1.x + (e1.x-s1.x) * s;
  v.y = s1.y + (e1.y-s1.y) * s;
  return 1;
}

bool bad(Line& a, Line& b, Line& c) {
  Point v;
  if (!line_intersect(a.s, a.t, b.s, b.t, v)) return 0;
  ld crs = (c.t-c.s) ^ (v-c.s);
  return crs < 0 || equals(crs, 0);
}

vector<Point> HPI(vector<Line>& ln) {
  auto lsgn = [&](const Line& a) {
    if(a.s.y == a.t.y) return a.s.x > a.t.x;
    return a.s.y > a.t.y;
  };
  sort(ln.begin(), ln.end(), [&](const Line& a, const Line& b) {
      if(lsgn(a) != lsgn(b)) return lsgn(a) < lsgn(b);
      return (a.t.x-a.s.x)*(b.t.y-b.s.y)-(a.t.y-a.s.y)*(b.t.x-b.s.x)>0;
    });
  deque<Line> dq;
  for(int i=0; i<ln.size(); i++) {
    while(dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), ln[i]))
      dq.pop_back();
    while(dq.size() >= 2 && bad(dq[0], dq[1], ln[i]))
      dq.pop_front();
    if(dq.size() < 2 || !bad(dq.back(), ln[i], dq[0]))
      dq.push_back(ln[i]);
  }
  vector<Point> res;
  if(dq.size() >= 3) {
    for(int i=0; i<dq.size(); i++) {
      int j=(i+1)%dq.size();
      Point v;
      if(!line_intersect(dq[i].s, dq[i].t, dq[j].s, dq[j].t, v)) continue;
      res.push_back(v);
    }
  }
  return res;
}
