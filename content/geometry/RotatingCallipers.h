/**
 * Author:
 * Description: A[0] should be mininum element, A should be a convex polygon and sorted in ccw.
 * Usage: 
 * Time: 
 */
#pragma once

ll rotating_calipers(vector<Point> A) {
  int n = A.size(); A.push_back(A[0]);
  int l = 0, r = 0;
  ll ret = 0;
  while(l < n) {
    // A[l], A[r] are antipodal points at this moment
    if(r+1 == l || ((A[l+1]-A[l])^(A[r+1]-A[r])) <= 0) l++;
    else r++;
  }
  return ret;
}
