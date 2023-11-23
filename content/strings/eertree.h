/**
 * Author:
 * Description: eertree.
 * Usage: add is same as suffix automaton. Note that c is 0-base.
 * Time: add is amortized O(1), $10^6$ add in 212ms.
 */
#pragma once

template <int MAXN>
struct eertree {
    struct Node {
        int len = 0, link = 0, cnt = 0;
        array<int, MAXN> nxt;
        Node() { fill(nxt.begin(), nxt.end(), -1); }
    };

    vector<int> S;
    vector<Node> V;
    int root = 0;

    eertree() {
        V.resize(2);
        V[0].len = -1;
    }
    
    void add(int c) {
        S.push_back(c);
        for(int tmp = root; ; tmp = V[tmp].link) {
            auto iter = S.rbegin()+V[tmp].len+1;
            if(iter < S.rend() && *iter == c) {
                if(V[tmp].nxt[c] == -1) {
                    root = V.size();
                    V[tmp].nxt[c] = root;
                    V.push_back(Node());
                    V.back().len = V[tmp].len+2;
                    tmp = V[tmp].link;
                    iter = S.rbegin()+V[tmp].len+1;
                    while(iter >= S.rend() || *iter != c) {
                        tmp = V[tmp].link;
                        iter = S.rbegin()+V[tmp].len+1;
                    }
                    tmp = V[tmp].nxt[c];
                    if(V.back().len == 1 || tmp <= 0) V.back().link = 1;
                    else V.back().link = tmp;
                } else root = V[tmp].nxt[c];
                V[root].cnt++;
                break;
            }
        }
    }
};
