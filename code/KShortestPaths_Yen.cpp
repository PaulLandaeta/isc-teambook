/*
  K-shortest loopless paths (Yen's algorithm) using Dijkstra for spur paths
  - yen_k_shortest_paths(n, adj, s, t, K)
  Note: adj: vector<vector<pair<int,long long>>> directed graph
*/

#include <bits/stdc++.h>
using namespace std;

using PLL = pair<long long, vector<int>>;

pair<long long, vector<int>> dijkstra_path(int n, const vector<vector<pair<int,long long>>>& adj, int s, int t){
  const long long INF=(1LL<<60); vector<long long> d(n,INF); vector<int> p(n,-1); d[s]=0;
  priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq; pq.push({0,s});
  while(!pq.empty()){
    auto [du,u]=pq.top(); pq.pop(); if(du!=d[u]) continue; if(u==t) break; for(auto [v,w]: adj[u]) if(du+w<d[v]) d[v]=du+w, p[v]=u, pq.push({d[v],v});
  }
  if(d[t]==INF) return {INF,{}}; vector<int> path; for(int v=t; v!=-1; v=p[v]) path.push_back(v); reverse(path.begin(), path.end()); return {d[t], path};
}

vector<PLL> yen_k_shortest_paths(int n, vector<vector<pair<int,long long>>> adj, int s, int t, int K){
  vector<PLL> A; auto first = dijkstra_path(n, adj, s, t); if(first.first> (1LL<<50)) return A; A.push_back(first);
  using State = pair<long long, vector<int>>; // cost, path
  set<pair<long long, vector<int>>> B;
  for(int k=1;k<K;++k){
    const auto& last = A.back().second; int L = last.size(); bool found=false;
    for(int i=0;i<L-1;++i){
      int spur = last[i]; vector<int> root(last.begin(), last.begin()+i+1);
      // Build a temporary graph removing edges that would create the same root-path
      vector<vector<pair<int,long long>>> g = adj;
      for(const auto& P : A){ const auto& path = P.second; if(path.size()>i && equal(root.begin(), root.end(), path.begin())){ int u = path[i], v = path[i+1]; // remove edge u->v
          g[u].erase(remove_if(g[u].begin(), g[u].end(), [&](auto &e){ return e.first==v; }), g[u].end()); }
      }
      // Remove nodes in root except spur
      unordered_set<int> ban(root.begin(), root.end()-1);
      // Dijkstra from spur to t avoiding banned nodes
      const long long INF=(1LL<<60); vector<long long> d(n,INF); vector<int> p(n,-1); d[spur]=0;
      priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq; pq.push({0,spur});
      while(!pq.empty()){
        auto [du,u]=pq.top(); pq.pop(); if(du!=d[u]) continue; if(u==t) break; for(auto [v,w]: g[u]) if(!ban.count(v) && du+w<d[v]) d[v]=du+w, p[v]=u, pq.push({d[v],v});
      }
      if(d[t]==INF) continue; vector<int> spurPath; for(int v=t; v!=-1; v=p[v]) spurPath.push_back(v); reverse(spurPath.begin(), spurPath.end());
      vector<int> total = root; total.pop_back(); total.insert(total.end(), spurPath.begin(), spurPath.end());
      long long rootCost=0; for(int j=0;j<(int)root.size()-1;++j){ int u=root[j], v=root[j+1]; for(auto [vv,w]: adj[u]) if(vv==v){ rootCost+=w; break;} }
      B.insert({rootCost + d[t], total}); found=true;
    }
    if(B.empty()) break; A.push_back(*B.begin()); B.erase(B.begin());
  }
  return A;
}

