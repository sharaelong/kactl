/**
 * Author:
 * Description: Return lyndon decomposition start positions and n.
 * Time: O(n), no data.
 */
#pragma once

vector<int> duval(string const& s) {
    vector<int> ret;
    int n = s.size();
    int i = 0;
    while(i < n) {
        int j = i+1, k = i;
        while(j < n && s[k] <= s[j]) {
            if(s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while(i <= k) {
            ret.push_back(i);
            i += j-k;
        }
    }
    ret.push_back(n);
    return ret;
}
