/**
 * Author:
 * Description: Centroid decomposition.
 * Usage: check for structure of decomposition.
 * Time:
 */
#pragma once

vector<int> adj[MAX_N];
int sz[MAX_N];
bool decomposed[MAX_N];
int ctpar[MAX_N];

int dfs(int here, int par = -1) {
  sz[here] = 1;
  for (int there: adj[here]) {
    if (there != par && !decomposed[there]) sz[here] += dfs(there, here);
  }
  return sz[here];
}

int get_cent(int here, int par, int capa) {
  for (int there: adj[here]) {
    if (there != par && !decomposed[there] && sz[there] > capa) return get_cent(there, here, capa);
  }
  return here;
}

void init(int here, int prev_cent = -1) {
  int size = dfs(here);
  int cent = get_cent(here, -1, size/2);
  decomposed[cent] = true;
  ctpar[cent] = prev_cent;
  for (int there: adj[cent]) {
    if (!decomposed[there]) {
      init(there, cent);
    }
  }
}

void update(int v) {
  for (int vp = v; vp != -1; vp = ctpar[vp]) { // do sth }
  }

  void solve() {
    init(1);
  }
