/**
 * Author:
 * Description:
 * Usage: 0-base. pmt[i] = s[0..i]'s common longest prefix and suffix. kmp[i] = ith matched begin position.
 * Time: O(n)
 */
#pragma once

vector<int> get_pmt(const string& s) {
    int n = s.size();
    vector<int> pmt(n, 0);
    // except finding itself by searching from s[0]
    int b = 1, m = 0;
    // s[b + m]: letter to compare
    while (b + m < n) {
        if (s[b+m] == s[m]) {
            pmt[b+m] = m + 1;
            m++;
        } else {
            if (m > 0) {
                b += m - pmt[m-1];
                m = pmt[m-1];
            } else {
                b++;
            }
        }
    }
    return pmt;
}
vector<int> KMP(const string& hay, const string& needle) {
    vector<int> pmt = get_pmt(needle);
    vector<int> ret;
    int b = 0, m = 0;
    while (b <= (int)hay.size() - needle.size()) {
        if (m < needle.size() && hay[b+m] == needle[m]) {
            m++;
            if (m == needle.size()) ret.push_back(b);
        } else {
            if (m > 0) {
                b += m - pmt[m-1];
                m = pmt[m-1];
            } else {
                b++;
            }
        }
    }
    return ret;
}
