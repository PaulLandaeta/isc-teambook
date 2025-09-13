/*
  Topological Sort (Kahn) and Longest Path in DAG
  - topo_order(n, adj): returns order (empty if cycle)
  - dag_longest_path(n, adj, weight): longest path distances assuming DAG
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> topo_order(int n, const vector<vector<int>>& adj){
  vector<int> indeg(n,0); for(int u=0;u<n;++u) for(int v:adj[u]) indeg[v]++;
  queue<int> q; for(int i=0;i<n;++i) if(!indeg[i]) q.push(i);
  vector<int> ord; ord.reserve(n);
  while(!q.empty()){ int u=q.front(); q.pop(); ord.push_back(u); for(int v:adj[u]) if(--indeg[v]==0) q.push(v); }
  if((int)ord.size()!=n) return {}; return ord;
}

// weight edges w[u][v] for (u->v). If no weight given, treat as 1.
vector<long long> dag_longest_path(int n, const vector<vector<pair<int,long long>>>& adj, int src){
  vector<vector<int>> g(n); for(int u=0;u<n;++u) for(auto [v,_]:adj[u]) g[u].push_back(v);
  auto ord = topo_order(n, g); vector<long long> dp(n, LLONG_MIN); if(ord.empty()) return dp; dp[src]=0;
  for(int u: ord){ if(dp[u]==LLONG_MIN) continue; for(auto [v,w]: adj[u]) dp[v] = max(dp[v], dp[u]+w); }
  return dp;
}

