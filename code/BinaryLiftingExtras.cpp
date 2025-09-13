/*
  Binary Lifting (LCA, k-th ancestor, jump length by predicate)
*/

#include <bits/stdc++.h>
using namespace std;

struct BinaryLifting {
  int n, LOG; vector<vector<int>> up; vector<int> depth; vector<vector<int>> g;
  BinaryLifting(int n=0){ init(n);} void init(int n_){ n=n_; LOG=1; while((1<<LOG)<=n) ++LOG; up.assign(LOG, vector<int>(n,-1)); depth.assign(n,0); g.assign(n,{});} 
  void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u);} 
  void dfs(int u,int p){ up[0][u]=p; for(int k=1;k<LOG;++k) up[k][u] = (up[k-1][u]==-1? -1 : up[k-1][ up[k-1][u] ]); for(int v:g[u]) if(v!=p){ depth[v]=depth[u]+1; dfs(v,u);} }
  void build(int root=0){ dfs(root,-1);} 
  int kth_ancestor(int u,int k){ for(int i=0;i<LOG && u!=-1;++i) if(k& (1<<i)) u=up[i][u]; return u; }
  int lca(int a,int b){ if(depth[a]<depth[b]) swap(a,b); a=kth_ancestor(a, depth[a]-depth[b]); if(a==b) return a; for(int k=LOG-1;k>=0;--k) if(up[k][a]!=up[k][b]) a=up[k][a], b=up[k][b]; return up[0][a]; }
  // jump while predicate holds: return the farthest ancestor of u such that pred(node) is true (including u)
  template<class F>
  int jump_by_pred(int u, F pred){ if(u==-1 || !pred(u)) return -1; for(int k=LOG-1;k>=0;--k){ int v=up[k][u]; if(v!=-1 && pred(v)) u=v; } return u; }
};

