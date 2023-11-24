/**
 * Author:
 * Description: Fast Delaunay triangulation.
 * Each circumcircle contains none of the input points.
 * There must be no duplicate points.
 * If all points are on a line, no triangles will be returned.
 * Should work for doubles as well, though there may be precision issues in 'circ'.
 * Returns triangles in order \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\}, all counter-clockwise.
 * Usage: vector<P> tris = triangulate(pts);
 * Time: O(n \log n), $\sum n \log n = 1.3 \times 10^7$ in 2500ms.
 */
#pragma once

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend istream& operator>>(istream& is, P& p) {
    return is >> p.x >> p.y; }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};


typedef Point<ll> P;
typedef __int128_t lll; // (can be ll if coords are < 2e4)
P arb(LLONG_MAX,LLONG_MAX); // not equal to any other point

struct Quad {
  int rot, o; P p = arb; bool mark;
  Quad(): rot(-1), o(-1), mark(false) {}
};

vector<Quad> qs;
int H = -1;

int& r(const Quad& q) { return qs[q.rot].rot; }
P& F(const Quad& q) { return qs[r(q)].p; }
int prev(const Quad& q) { return qs[qs[q.rot].o].rot; }
int next(const Quad& q) { return prev(qs[r(q)]); }

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
  lll p2 = p.dist2(), A = a.dist2()-p2,
    B = b.dist2()-p2, C = c.dist2()-p2;
  return p.cross(a,b)*C + p.cross(b,c)*A + p.cross(c,a)*B > 0;
}
int makeEdge(P orig, P dest) {
  int rr;
  if (H != -1) {
    rr = H;
  } else {
    qs.push_back(Quad());
    int sz = qs.size()-1;
    qs.push_back(Quad());
    qs.back().rot = sz;
    sz = qs.size()-1;
    qs.push_back(Quad());
    qs.back().rot = sz;
    sz = qs.size()-1;
    qs.push_back(Quad());
    qs.back().rot = sz;
    rr = qs.size()-1;
  }
  H = qs[rr].o; r(qs[r(qs[rr])]) = rr;
  rep(i,0,4) rr = qs[rr].rot, qs[rr].p = arb, qs[rr].o = i & 1 ? rr : r(qs[rr]);
  qs[rr].p = orig; F(qs[rr]) = dest;
  return rr;
}

void splice(int a, int b) {
  swap(qs[qs[qs[a].o].rot].o, qs[qs[qs[b].o].rot].o); swap(qs[a].o, qs[b].o);
}

int connect(int a, int b) {
  int q = makeEdge(F(qs[a]), qs[b].p);
  splice(q, next(qs[a]));
  splice(r(qs[q]), b);
  return q;
}

pair<int,int> rec(const vector<P>& s) {
  if (sz(s) <= 3) {
    int a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
    if (sz(s) == 2) return { a, r(qs[a]) };
    splice(r(qs[a]), b);
    auto side = s[0].cross(s[1], s[2]);
    int c = side ? connect(b, a) : 0;
    return {side < 0 ? r(qs[c]) : a, side < 0 ? c : r(qs[b])};
  }

#define H(e) F(qs[e]), qs[e].p
#define valid(e) (F(qs[e]).cross(H(base)) > 0)
  int A, B, ra, rb;
  int half = sz(s) / 2;
  tie(ra, A) = rec({all(s) - half});
  tie(B, rb) = rec({sz(s) - half + all(s)});
  while ((qs[B].p.cross(H(A)) < 0 && (A = next(qs[A]))) ||
         (qs[A].p.cross(H(B)) > 0 && (B = qs[r(qs[B])].o)));
  int base = connect(r(qs[B]), A);
  if (qs[A].p == qs[ra].p) ra = r(qs[base]);
  if (qs[B].p == qs[rb].p) rb = base;

  for (;;) {
    int LC = qs[r(qs[base])].o;
    if (valid(LC)) {
      while (circ(F(qs[qs[LC].o]), H(base), F(qs[LC]))) {
        int t = qs[LC].o;
        splice(LC, prev(qs[LC]));
        splice(r(qs[LC]), prev(qs[r(qs[LC])]));
        qs[LC].o = H; H = LC; LC = t;              
      }
    }
    int RC = prev(qs[base]);
    if (valid(RC)) {
      while (circ(F(qs[prev(qs[RC])]), H(base), F(qs[RC]))) {
        int t = prev(qs[RC]);
        splice(RC, prev(qs[RC]));
        splice(r(qs[RC]), prev(qs[r(qs[RC])]));
        qs[RC].o = H; H = RC; RC = t;              
      }
    }
    if (!valid(LC) && !valid(RC)) break;
    if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
      base = connect(RC, r(qs[base]));
    else
      base = connect(r(qs[base]), r(qs[LC]));
  }
  return { ra, rb };
}

vector<P> triangulate(vector<P> pts) {
  sort(all(pts));  assert(unique(all(pts)) == pts.end());
  if (sz(pts) < 2) return {};
  int e = rec(pts).first;
  vector<int> q = {e};
  int qi = 0;
  while (F(qs[qs[e].o]).cross(F(qs[e]), qs[e].p) < 0) e = qs[e].o;
#define ADD { int c = e; do { qs[c].mark = 1; pts.push_back(qs[c].p);   \
      q.push_back(r(qs[c])); c = next(qs[c]); } while (c != e); }
  ADD; pts.clear();
  while (qi < sz(q)) if (!qs[(e = q[qi++])].mark) ADD;
  return pts;
}
