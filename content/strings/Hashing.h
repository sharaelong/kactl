/**
 * Author:
 * Description:
 * Usage: Hashing<base, mod> hsh; hsh.Build(s); query is 1-base (but s is not modified).
 */
#pragma once

// 1e5+3, 1e5+13, 131'071, 524'287, 1'299'709, 1'301'021
// 1e9-63, 1e9+7, 1e9+9, 1e9+103
template<ll P, ll M> struct Hashing {
    vector<ll> H, B;
    void Build(const string &S){
        H.resize(S.size()+1);
        B.resize(S.size()+1);
        B[0] = 1;
        for(int i=1; i<=S.size(); i++) H[i] = (H[i-1] * P + S[i-1]) % M;
        for(int i=1; i<=S.size(); i++) B[i] = B[i-1] * P % M;
    }
    ll sub(int s, int e){
        ll res = (H[e] - H[s-1] * B[e-s+1]) % M;
        return res < 0 ? res + M : res;
    }
};
