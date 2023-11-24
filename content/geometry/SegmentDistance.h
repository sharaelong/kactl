/**
 * Author:
 * Description:
 */
#pragma once

ld proj_height(Point a, Point b, Point x) {
  ld t1 = (b-a) * (x-a), t2 = (a-b) * (x-b);
  if (sgn(t1*t2) >= 0) return abs((b-a)^(x-a)) / (b-a).norm();
  else return 1e18;
}

ld segment_dist(Point s1, Point e1, Point s2, Point e2) {
  ld ans = 1e18;
  ans = min(ans, (s2-s1).norm());
  ans = min(ans, (e2-s1).norm());
  ans = min(ans, (s2-e1).norm());
  ans = min(ans, (e2-e1).norm());
  ans = min(ans, proj_height(s1, e1, s2));
  ans = min(ans, proj_height(s1, e1, e2));
  ans = min(ans, proj_height(s2, e2, s1));
  ans = min(ans, proj_height(s2, e2, e1));
  return ans;
}
