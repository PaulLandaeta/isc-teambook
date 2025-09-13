/*
  Bellman-Ford and SPFA with negative cycle detection
  - bellman_ford(n, edges, src): returns dist, and vector<bool> inNegCycle
  - spfa(n, adj, src): heuristic, also detect negative cycle if a node relaxes >= n times
*/

#include <bits/stdc++.h>
using namespace std;

struct E { int u,v; long long w; };

pair<vector<long long>, vector<char>> bellman_ford(int n, const vector<E>& edges, int src){
  const long long INF = (1LL<<60); vector<long long> d(n, INF); d[src]=0;
  for(int i=0;i<n-1;++i){ bool any=false; for(auto &e:edges){ if(d[e.u]<INF && d[e.u]+e.w<d[e.v]){ d[e.v]=d[e.u]+e.w; any=true; } } if(!any) break; }
  vector<char> inNeg(n,0); for(auto &e:edges){ if(d[e.u]<INF && d[e.u]+e.w<d[e.v]) inNeg[e.v]=1; }
  // propagate negativity
  queue<int> q; for(int i=0;i<n;++i) if(inNeg[i]) q.push(i);
  vector<vector<int>> g(n); for(auto &e:edges) g[e.u].push_back(e.v);
  while(!q.empty()){ int u=q.front(); q.pop(); for(int v:g[u]) if(!inNeg[v]) inNeg[v]=1, q.push(v); }
  return {d, inNeg};
}

pair<vector<long long>, vector<char>> spfa(int n, const vector<vector<pair<int,long long>>>& adj, int src){
  const long long INF=(1LL<<60); vector<long long> d(n,INF); vector<int> cnt(n,0); vector<char> inq(n,0), inNeg(n,0);
  deque<int> q; d[src]=0; q.push_back(src); inq[src]=1;
  while(!q.empty()){
    int u=q.front(); q.pop_front(); inq[u]=0;
    for(auto [v,w]: adj[u]) if(d[u]+w<d[v]){
      d[v]=d[u]+w; if(!inq[v]){ if(!q.empty() && d[v]<d[q.front()]) q.push_front(v); else q.push_back(v); inq[v]=1; }
      if(++cnt[v]>=n){ inNeg[v]=1; }
    }
  }
  // propagate negative cycles
  queue<int> z; for(int i=0;i<n;++i) if(inNeg[i]) z.push(i);
  while(!z.empty()){ int u=z.front(); z.pop(); for(auto [v,_]: adj[u]) if(!inNeg[v]) inNeg[v]=1, z.push(v); }
  return {d, inNeg};
}

