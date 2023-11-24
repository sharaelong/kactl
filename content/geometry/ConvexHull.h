/**
 * Author:
 * Description: collinear points removal is optional. Return points are sorted in ccw.
 * Time: O(n \log n)
 */
#pragma once

vector <Point> convex_hull(vector <Point> P){ // coliinear points are not removed
  vector <Point> up, down;
  sort(P.begin(), P.end());
  for (Point now : P){
    while (up.size() >= 2 && ((up.back() - up[up.size() - 2])^(now - up[up.size() - 2])) > 0) up.pop_back(); // >=0 : remove collinear points
    up.push_back(now);
    while (down.size() >= 2 && ((down.back() - down[down.size() - 2])^(now - down[down.size() - 2])) < 0) down.pop_back(); // <=0 : remove collinear points
    down.push_back(now);
  }
  down.insert(down.end(), up.rbegin()+1, up.rend()-1);
  return down;
}
