/*
  Euler Tour (flatten tree) + BIT/SegTree mapping
  - subtree of u => [tin[u], tout[u])
  - path queries via HLD (see separate file) or using LCA
*/

#include <bits/stdc++.h>
using namespace std;

struct EulerTour {
  int n; vector<vector<int>> g; vector<int> tin, tout, euler; int t=0;
  EulerTour(int n=0): n(n), g(n), tin(n), tout(n) {}
  void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }
  void dfs(int u,int p){ tin[u]=t++; euler.push_back(u); for(int v:g[u]) if(v!=p) dfs(v,u); tout[u]=t; }
  void build(int root=0){ euler.clear(); t=0; dfs(root,-1); }
};

