/**
 * Author:
 * Description:
 * Usage: add(c) adds c at the end of string. topo(f) executes f while topological sort when erase edges. f(x, y, c): y->x edge marked as c. Note that c is 0-base.
 * Time: add is amortized O(1), topo is O(n), no data. $10^6$ add call and one topo call in 668ms.
 */
#pragma once

template <int MAXN>
struct SuffixAutomaton {
  struct Node {
    int nxt[MAXN];
    int len = 0, link = 0;
    Node() { memset(nxt, -1, sizeof nxt); }
  };

  int root = 0;
  vector<Node> V;
    
  SuffixAutomaton() {
    V.resize(1);
    V.back().link = -1;
  }

  void add(int c) {
    V.push_back(Node());
    V.back().len = V[root].len+1;
    int tmp = root;
    root = (int)V.size()-1;
    while(tmp != -1 && V[tmp].nxt[c] == -1) {
      V[tmp].nxt[c] = root;
      tmp = V[tmp].link;
    }
    if(tmp != -1) {
      int x = V[tmp].nxt[c];
      if(V[tmp].len+1 < V[x].len) {
        int y = x;
        x = (int)V.size();
        V.push_back(V[y]);
        V.back().len = V[tmp].len+1;
        V[y].link = x;
        while(tmp != -1 && V[tmp].nxt[c] == y) {
          V[tmp].nxt[c] = x;
          tmp = V[tmp].link;
        }
      }
      V[root].link = x;
    }
  }

  void topo(function<void(int, int, int)> f) {
    vector<int> indeg(V.size(), 0);
    for(auto &node : V) {
      for(auto j : node.nxt) {
        if(j == -1) continue;
        indeg[j]++;
      }
    }
    queue<int> Q;
    for(int i = 0; i < (int)indeg.size(); i++)
      if(indeg[i] == 0) Q.push(i);
    while(Q.size()) {
      int tmp = Q.front(); Q.pop();
      auto &node = V[tmp];
      for(int j = 0; j < MAXN; j++) {
        if(node.nxt[j] == -1) continue;
        f(node.nxt[j], tmp, j);
        if(--indeg[node.nxt[j]] == 0)
          Q.push(node.nxt[j]);
      }
    }
  }
};
