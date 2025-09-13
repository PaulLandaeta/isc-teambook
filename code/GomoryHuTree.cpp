/*
  Gomory-Hu Tree (undirected) - builds min-cut tree using maxflow (Dinic)
  - build(n, edges): edges as (u,v,w)
  - returns parent array and weight (mincut) of edge to parent
*/

#include <bits/stdc++.h>
using namespace std;

struct DinicGH {
  struct E{ int to; long long cap; int rev; }; int n; vector<vector<E>> g; vector<int> lvl, it;
  DinicGH(int n=0){init(n);} void init(int n_){ n=n_; g.assign(n,{});} 
  void add_edge(int u,int v,long long c){ E a{v,c,(int)g[v].size()}, b{u,c,(int)g[u].size()}; g[u].push_back(a); g[v].push_back(b); }
  bool bfs(int s,int t){ lvl.assign(n,-1); queue<int> q; lvl[s]=0; q.push(s); while(!q.empty()){ int u=q.front(); q.pop(); for(auto &e:g[u]) if(e.cap>0 && lvl[e.to]==-1) lvl[e.to]=lvl[u]+1, q.push(e.to);} return lvl[t]!=-1; }
  long long dfs(int u,int t,long long f){ if(u==t||f==0) return f; for(int &i=it[u]; i<(int)g[u].size(); ++i){ auto &e=g[u][i]; if(e.cap>0 && lvl[e.to]==lvl[u]+1){ long long got=dfs(e.to,t,min(f,e.cap)); if(got){ e.cap-=got; g[e.to][e.rev].cap+=got; return got; } } } return 0; }
  long long maxflow(int s,int t){ long long flow=0; while(bfs(s,t)){ it.assign(n,0); while(long long f=dfs(s,t,LLONG_MAX)) flow+=f; } return flow; }
};

pair<vector<int>, vector<long long>> gomory_hu(int n, const vector<tuple<int,int,long long>>& edges){
  vector<int> parent(n,0); vector<long long> w(n,0);
  for(int i=1;i<n;++i){
    DinicGH D(n); for(auto [u,v,c]: edges){ D.add_edge(u,v,c); }
    int s=i, t=parent[i];
    w[i] = D.maxflow(s,t);
    vector<char> side(n,0); queue<int> q; q.push(s); side[s]=1; while(!q.empty()){ int u=q.front(); q.pop(); for(auto &e: D.g[u]) if(e.cap>0 && !side[e.to]) side[e.to]=1, q.push(e.to); }
    for(int j=i+1;j<n;++j) if(parent[j]==t && side[j]) parent[j]=i;
    if(side[parent[t]]){ parent[i]=parent[t]; parent[t]=i; swap(w[i], w[t]); }
  }
  return {parent, w};
}
