/**
 * Author:
 * Description: Computes the minimum circle that encloses a set of points. Expect that point list is shuffled.
 * Time: expected O(n)
 */
#pragma once

struct Circle{ Point p; double r; };

long double dst(Point a, Point b); // root of square dist
Point getCenter(Point a, Point b){ return {(a.x+b.x)/2, (a.y+b.y)/2}; } // center of two points
Point getCenter(Point a, Point b, Point c){ // center of circumcircle of triangle
  Point aa = b - a, bb = c - a;
  auto c1 = aa*aa * 0.5, c2 = bb*bb * 0.5;
  auto d = aa ^ bb;
  auto x = a.x + (c1 * bb.y - c2 * aa.y) / d;
  auto y = a.y + (c2 * aa.x - c1 * bb.x) / d;
  return {x, y};
}

Circle solve(vector<Point> v){
  Point p = {0, 0};
  double r = 0; int n = v.size();
  for(int i=0; i<n; i++) if(dst(p, v[i]) > r){ //break point 1
      p = v[i]; r = 0;
      for(int j=0; j<i; j++) if(dst(p, v[j]) > r){ //break point 2
          p = getCenter(v[i], v[j]); r = dst(p, v[i]);
          for(int k=0; k<j; k++) if(dst(p, v[k]) > r){ //break point 3
              p = getCenter(v[i], v[j], v[k]);
              r = dst(v[k], p);
            }
        }
    }
  return {p, r};
}
