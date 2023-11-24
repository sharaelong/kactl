/**
 * Author:
 * Description: Return compressed node index of dual graph of each edge's both side. Second index is inf out face of dual graph. Even number is left side of edge oriented to dictionary order increasing.
 * Time: O(n \log n)
 */
#pragma once

constexpr int quadrant_id(const Point p){
  constexpr int arr[9] = { 5, 4, 3, 6, -1, 2, 7, 0, 1 };
  return arr[sign(p.x)*3+sign(p.y)+4];
}
pair<vector<int>, int> dual_graph(const vector<Point> &points, const vector<pair<int,int>> &edges){
  int n = points.size(), m = edges.size();
  vector<int> uf(2*m); iota(uf.begin(), uf.end(), 0);
  function<int(int)> find = [&](int v){ return v == uf[v] ? v : uf[v] = find(uf[v]); };
  function<bool(int,int)> merge = [&](int u, int v){ return find(u) != find(v) && (uf[uf[u]]=uf[v], true); };
  vector<vector<pair<int,int>>> g(n);
  for(int i=0; i<m; i++){
    g[edges[i].first].emplace_back(edges[i].second, i);
    g[edges[i].second].emplace_back(edges[i].first, i);
  }
  for(int i=0; i<n; i++){
    const auto base = points[i];
    sort(g[i].begin(), g[i].end(), [&](auto a, auto b){
        auto p1 = points[a.first] - base, p2 = points[b.first] - base;
        return quadrant_id(p1) != quadrant_id(p2) ? quadrant_id(p1) < quadrant_id(p2) : (p1 ^ p2) > 0;
      });
    for(int j=0; j<g[i].size(); j++){
      int k = j ? j - 1 : g[i].size() - 1;
      int u = g[i][k].second << 1, v = g[i][j].second << 1 | 1;
      auto p1 = points[g[i][k].first], p2 = points[g[i][j].first];
      if(p1 < base) u ^= 1; if(p2 < base) v ^= 1;
      merge(u, v);
    }
  }
  vector<int> res(2*m);
  for(int i=0; i<2*m; i++) res[i] = find(i);
  auto comp = res; sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());
  for(auto &i : res) i = lower_bound(comp.begin(), comp.end(), i) - comp.begin();
  int mx_idx = max_element(points.begin(), points.end()) - points.begin();
  return {res, res[g[mx_idx].back().second << 1 | 1]};
}
