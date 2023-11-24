/**
 * Author:
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Usage: 
 * Time: Build $O(26n)$, find $O(n)$. Build $10^5$, find $10^7$ in 132ms.
 */
#pragma once

struct Node {
  Node *go[26], *fail;
  bool end;
Node() : fail(nullptr), end(false) { fill(go, go + 26, nullptr); }
  ~Node() {
    for (Node *next: go)
      if (next) delete next;
  }
};

Node * build_trie(vector<string> &patterns) {
  Node *root = new Node();

  for (string &p: patterns) {
    Node *curr = root;
    for (char c: p) {
      if (!curr->go[c - 'a']) curr->go[c - 'a'] = new Node();
      curr = curr->go[c - 'a'];
    }
    curr->end = true;
  }

  queue<Node *> q; q.push(root);
  root->fail = root;

  while (!q.empty()) {
    Node *curr = q.front(); q.pop();
    for (int i = 0; i < 26; i++) {
      Node *next = curr->go[i];
      if (!next) continue;
      q.push(next);

      if (curr == root) next->fail = root;
      else {
        Node *dest = curr->fail;
        while (dest != root && !dest->go[i]) dest = dest->fail;
        if (dest->go[i]) dest = dest->go[i];
        next->fail = dest;
        next->end |= dest->end;
      }
    }
  }

  return root;
}

bool find_trie(Node *trie, string &s) {
  Node *curr = trie;
  for (char c: s) {
    while (curr != trie && !curr->go[c - 'a']) curr = curr->fail;
    if (curr->go[c - 'a']) curr = curr->go[c - 'a'];
    if (curr->end) return true;
  }
  return false;
}
