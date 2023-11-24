/**
 * Author:
 * Description:
 * Usage: mana[i] stores radius of maximal palindrome of intervened string. Single char is radius 0. Max element of mana is equal to real longest palindrome length.
 * Time: O(N), $N = 10^5$ in 4ms.
 */
#pragma once

vector<int> mana(string &s) {
  string t = ".";
  for(auto i : s) { t += i; t += '.'; }
  vector<int> ret(t.size(), 0);
  for(int i = 0, c = 0, r = 0; i < (int)t.size(); i++) {
    if(i < r) ret[i] = min(r-i, ret[2*c-i]);
    while(i-ret[i]-1 >= 0 && i+ret[i]+1 < (int)t.size() && t[i-ret[i]-1] == t[i+ret[i]+1]) ret[i]++;
    if(r < i+ret[i]) r = i+ret[i], c = i;
  }
  return ret;
}
