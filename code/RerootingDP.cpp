/*
  Rerooting DP on trees (generic template)
  - Combine child contributions with associative op, add root with add_root
  - Example computes subtree sizes and for each node the size of its subtree when rooted at that node (trivial example)
*/

#include <bits/stdc++.h>
using namespace std;

struct RerootingDP {
  int n; vector<vector<int>> g;
  // DP value type
  struct V { long long val=0; };
  V id() const { return V{0}; }
  V merge(const V& a, const V& b) const { return V{a.val + b.val}; }
  V add_root(const V& a, int u) const { return V{a.val + 1}; }

  vector<V> down, up, ans;
  RerootingDP(int n=0): n(n), g(n), down(n), up(n), ans(n) {}
  void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }

  void dfs_down(int u,int p){ V acc = id(); for(int v: g[u]) if(v!=p){ dfs_down(v,u); acc = merge(acc, add_root(down[v], v)); } down[u] = acc; }
  void dfs_up(int u,int p){ int m=g[u].size(); vector<V> pref(m+1, id()), suf(m+1, id());
    for(int i=0;i<m;++i){ int v=g[u][i]; V contrib = (v==p? id(): add_root(down[v], v)); pref[i+1] = merge(pref[i], contrib); }
    for(int i=m-1;i>=0;--i){ int v=g[u][i]; V contrib = (v==p? id(): add_root(down[v], v)); suf[i] = merge(suf[i+1], contrib); }
    for(int i=0;i<m;++i){ int v=g[u][i]; if(v==p) continue; V without = merge(pref[i], suf[i+1]); V from_parent = add_root(merge(without, up[u]), u); up[v] = from_parent; dfs_up(v,u); }
  }
  vector<V> solve(int root=0){ dfs_down(root,-1); up[root]=id(); dfs_up(root,-1); for(int u=0;u<n;++u) ans[u] = add_root(merge(down[u], up[u]), u); return ans; }
};

