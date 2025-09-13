/*
  Title: LCA (Binary Lifting)
  Complexity: Build O(n log n), Query O(log n)
  Description: Lowest Common Ancestor on a tree. Add edges with addEdge(u,v), then build(root).
  Example:
  // int main(){
  //   LCA lca(5);
  //   lca.addEdge(0,1); lca.addEdge(1,2); lca.addEdge(1,3); lca.addEdge(3,4);
  //   lca.build(0);
  //   cout << lca.query(2,4) << "\n"; // 1
  // }
*/

#include <bits/stdc++.h>
using namespace std;

struct LCA {
  int n, LOG; vector<vector<int>> up; vector<int> depth; vector<vector<int>> g;
  LCA(int n): n(n), LOG(1), up(), depth(n,0), g(n) { while((1<<LOG) <= n) ++LOG; up.assign(LOG, vector<int>(n, -1)); }
  void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }
  void dfs(int u,int p){ up[0][u]=p; for(int k=1;k<LOG;++k) up[k][u] = (up[k-1][u]==-1? -1 : up[k-1][ up[k-1][u] ]); for(int v: g[u]) if(v!=p){ depth[v]=depth[u]+1; dfs(v,u);} }
  void build(int root){ depth[root]=0; dfs(root,-1); }
  int kth_ancestor(int u,int k){ for(int i=0;i<LOG && u!=-1;++i) if(k&(1<<i)) u=up[i][u]; return u; }
  int query(int a,int b){ if(depth[a]<depth[b]) swap(a,b); a=kth_ancestor(a, depth[a]-depth[b]); if(a==b) return a; for(int k=LOG-1;k>=0;--k) if(up[k][a]!=up[k][b]){ a=up[k][a]; b=up[k][b]; } return up[0][a]; }
};
