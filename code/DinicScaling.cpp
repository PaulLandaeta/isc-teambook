/*
  Dinic with capacity scaling wrapper
  - Improves performance on graphs with large capacities
*/

#include <bits/stdc++.h>
using namespace std;

struct DinicScaling {
  struct Edge{ int to; long long cap; int rev; };
  int n; vector<vector<Edge>> g; vector<int> lvl, it; long long LIM;
  DinicScaling(int n=0){ init(n);} void init(int n_){ n=n_; g.assign(n,{});} 
  void add_edge(int u,int v,long long c){ Edge a{v,c,(int)g[v].size()}, b{u,0,(int)g[u].size()}; g[u].push_back(a); g[v].push_back(b); }
  bool bfs(int s,int t){ fill(lvl.begin(),lvl.end(),-1); queue<int> q; lvl[s]=0; q.push(s); while(!q.empty()){ int u=q.front(); q.pop(); for(auto &e:g[u]) if(e.cap>=LIM && lvl[e.to]==-1){ lvl[e.to]=lvl[u]+1; q.push(e.to);} } return lvl[t]!=-1; }
  long long dfs(int u,int t,long long f){ if(u==t || f==0) return f; for(int &i=it[u]; i<(int)g[u].size(); ++i){ auto &e=g[u][i]; if(e.cap>=LIM && lvl[e.to]==lvl[u]+1){ long long got=dfs(e.to,t,min(f,e.cap)); if(got){ e.cap-=got; g[e.to][e.rev].cap+=got; return got; } } } return 0; }
  long long maxflow(int s,int t){ long long flow=0; long long maxcap=0; for(int u=0;u<n;++u) for(auto &e:g[u]) maxcap=max(maxcap,e.cap); lvl.assign(n,-1); it.assign(n,0); for(LIM=1LL<<62; LIM>0; LIM>>=1){ if(LIM>maxcap) continue; while(bfs(s,t)){ fill(it.begin(),it.end(),0); while(long long f=dfs(s,t,LLONG_MAX)) flow+=f; } } return flow; }
};

