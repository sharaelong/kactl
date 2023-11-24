/**
 * Author:
 * Description:
 * Usage: Z[i] stores lcp of s[0..] and s[i..]
 * Time: O(n), $N = 10^5$ in 20ms.
 */
#pragma once

vector<int> Z(string &s) {
  vector<int> ret(s.size(), 0); ret[0] = s.size();
  for(int i = 1, l = 0, r = 1; i < s.size(); i++) {
    ret[i] = max(0, min(ret[i-l], r-i));
    while(ret[i]+i < s.size() && s[i+ret[i]] == s[ret[i]]) ret[i]++;
    if(i+ret[i] > r) r = i+ret[i], l = i;
  }
  return ret;
}
