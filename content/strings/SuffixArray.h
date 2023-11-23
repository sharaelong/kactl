/**
 * Author:
 * Description:
 * Usage: 0-base index. sa[i]: lexicographically (i+1)'th suffix (of d letters). lcp[i]: lcp between sa[i] and sa[i+1]. r[i]: rank of s[i..n-1] when only consider first d letters. nr: temp array for next rank. cnt[i]: number of positions which has i of next rank. rf[r]: lexicographically first position which suffixes (of d letters) has rank r. rdx[i]: lexicographically (i+1)'th suffix when only consider (d+1)'th ~ 2d'th letters.
 * Time: O(n \log n), $N = 5 \times 10^5$ in 176ms.
 */

#pragma once

void suffix_array(string S, vector<int> &sa, vector<int> &lcp) {
    int n = S.size();
    vector<int> r(n), nr(n), rf(n), rdx(n);
    sa.resize(n); lcp.resize(n);

    for (int i = 0; i < n; i++) sa[i] = i;
    sort(sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
    for (int i = 1; i < n; i++) r[sa[i]] = r[sa[i - 1]] + (S[sa[i - 1]] != S[sa[i]]);

    for (int d = 1; d < n; d <<= 1) {
        for (int i = n - 1; i >= 0; i--) {
            rf[r[sa[i]]] = i;
        }
        int j = 0;
        for (int i = n - d; i < n; i++) rdx[j++] = i;
        for (int i = 0; i < n; i++) {
            if (sa[i] >= d) rdx[j++] = sa[i] - d;
        }
        for (int i = 0; i < n; i++) {
            sa[rf[r[rdx[i]]]++] = rdx[i];
        }
        nr[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (r[sa[i]] != r[sa[i - 1]]) {
                nr[sa[i]] = nr[sa[i - 1]] + 1;
            }
            else {
                int prv = (sa[i - 1] + d >= n ? -1 : r[sa[i - 1] + d]);
                int cur = (sa[i] + d >= n ? -1 : r[sa[i] + d]);
                nr[sa[i]] = nr[sa[i - 1]] + (prv != cur);
            }
        }
        swap(r, nr);
        if (r[sa[n-1]] == n-1) break;
    }
    for (int i = 0, len = 0; i < n; ++i, len = max(len - 1, 0)) {
        if (r[i] == n - 1) continue;
        for (int j = sa[r[i] + 1]; S[i + len] == S[j + len]; ++len);
        lcp[r[i]] = len;
    }
}
