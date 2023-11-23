/**
 * Author:
 * Description: Finds the lexicographically smallest rotation of a string.
 * Time: O(N), no data.
 */
#pragma once

string min_cyclic_string(string s) {
    int n = s.size();
    s += s;
    int i = 0, ans = 0;
    while(i < n) {
        ans = i;
        int j = i+1, k = i;
        while(j < 2*n && s[k] <= s[j]) {
            if(s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while(i <= k) i += j-k;
    }
    return s.substr(ans, n);
}
