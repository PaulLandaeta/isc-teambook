/*
  Title: SCC (Kosaraju)
  Complexity: O(V + E)
  Description: Strongly Connected Components on directed graph.
  Example:
  // int main(){
  //   SCC scc(5);
  //   scc.addEdge(0,1); scc.addEdge(1,2); scc.addEdge(2,0); scc.addEdge(1,3);
  //   auto comp = scc.solve(); // comp[i] is component id
  // }
*/

#include <bits/stdc++.h>
using namespace std;

struct SCC {
  int n; vector<vector<int>> g, gr; vector<int> comp, order; vector<char> used;
  SCC(int n): n(n), g(n), gr(n) {}
  void addEdge(int u,int v){ g[u].push_back(v); gr[v].push_back(u); }
  void dfs1(int v){ used[v]=1; for(int to: g[v]) if(!used[to]) dfs1(to); order.push_back(v); }
  void dfs2(int v,int c){ comp[v]=c; for(int to: gr[v]) if(comp[to]==-1) dfs2(to,c); }
  vector<int> solve(){ used.assign(n,0); order.clear(); for(int i=0;i<n;++i) if(!used[i]) dfs1(i); comp.assign(n,-1); int j=0; for(int i=n-1;i>=0;--i){ int v=order[i]; if(comp[v]==-1) dfs2(v,j++); } return comp; }
};
