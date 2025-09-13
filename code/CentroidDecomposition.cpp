/*
  Centroid Decomposition of a tree
  - decompose(root): builds centroid tree, calls a user hook on each centroid
  - Example collects parent in centroid tree
*/

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
  int n; vector<vector<int>> g; vector<int> sz, par; vector<char> dead;
  CentroidDecomposition(int n=0): n(n), g(n), sz(n), par(n,-1), dead(n,0) {}
  void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }
  int dfs_sz(int u,int p){ sz[u]=1; for(int v:g[u]) if(v!=p && !dead[v]) sz[u]+=dfs_sz(v,u); return sz[u]; }
  int find_centroid(int u,int p,int total){ for(int v:g[u]) if(v!=p && !dead[v] && sz[v]*2>total) return find_centroid(v,u,total); return u; }
  void solve_subtree(int c){ /* user hook for processing at centroid c */ }
  void decompose(int u,int p=-1){ int total=dfs_sz(u,-1); int c=find_centroid(u,-1,total); par[c]=p; dead[c]=1; solve_subtree(c); for(int v:g[c]) if(!dead[v]) decompose(v,c); }
};

