/*
  Bridges, Articulation Points, and Biconnected Components (edge-BCC)
  - bridges, cut vertices via DFS lowlink
  - edge-biconnected components: comp id per edge (undirected)
*/

#include <bits/stdc++.h>
using namespace std;

struct Biconnected {
  int n; vector<vector<pair<int,int>>> g; // to, edge id
  vector<int> tin, low; vector<char> is_bridge, is_cut; int timer=0;
  vector<int> comp; int comps=0; // edge comp id
  Biconnected(int n=0):n(n),g(n){}
  void addEdge(int u,int v,int id){ g[u].push_back({v,id}); g[v].push_back({u,id}); }
  void dfs(int v,int pe){ tin[v]=low[v]=++timer; int child=0; for(auto [to,id]: g[v]) if(id!=pe){ if(!tin[to]){ child++; dfs(to,id); low[v]=min(low[v], low[to]); if(low[to] > tin[v]) is_bridge[id]=1; if(pe==-1 && child>1) is_cut[v]=1; if(pe!=-1 && low[to] >= tin[v]) is_cut[v]=1; } else low[v]=min(low[v], tin[to]); }
  }
  void build(int m){ tin.assign(n,0); low.assign(n,0); is_bridge.assign(m,0); is_cut.assign(n,0); timer=0; for(int i=0;i<n;++i) if(!tin[i]) dfs(i,-1); }
};

