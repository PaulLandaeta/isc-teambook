/*
  MST (Kruskal + Prim) and critical edges recovery (Kruskal-groups + bridges)
  - kruskal(n, edges) -> {mst_weight, mst_edges(ids)}
  - prim(n, adj) -> mst_weight (0 if disconnected)
  - critical_edges_kruskal(n, edges): vector<bool> is_critical per edge id

  Edge format for Kruskal/critical: {u,v,w,id} with 0<=id<m
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU { vector<int> p, r; DSU(int n=0){init(n);} void init(int n){ p.resize(n); iota(p.begin(),p.end(),0); r.assign(n,0);} int f(int x){ return p[x]==x?x:p[x]=f(p[x]); } bool u(int a,int b){ a=f(a); b=f(b); if(a==b) return false; if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; return true; } };

struct Edge {int u,v; long long w; int id;};

pair<long long, vector<int>> kruskal(int n, vector<Edge> e){
  sort(e.begin(), e.end(), [](const Edge& a, const Edge& b){ return a.w < b.w; });
  DSU d(n); long long W=0; vector<int> ids;
  for(auto &E: e) if(d.u(E.u,E.v)){ W += E.w; ids.push_back(E.id);} 
  if((int)ids.size() != n-1) return {0, {}}; // disconnected
  return {W, ids};
}

long long prim(int n, const vector<vector<pair<int,long long>>>& adj){
  vector<char> vis(n,0); priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
  long long W=0; int cnt=0; pq.push({0,0});
  while(!pq.empty()){
    auto [w,u]=pq.top(); pq.pop(); if(vis[u]) continue; vis[u]=1; W+=w; cnt++; for(auto [v,ww]: adj[u]) if(!vis[v]) pq.push({ww,v});
  }
  return cnt==n? W : 0;
}

// Critical edges via Kruskal groups + bridges on the contracted group-graph
vector<char> critical_edges_kruskal(int n, vector<Edge> e){
  vector<char> critical(e.size(), 0);
  sort(e.begin(), e.end(), [](const Edge& a, const Edge& b){ if(a.w!=b.w) return a.w<b.w; return a.id<b.id; });
  DSU d(n);
  for(size_t i=0;i<e.size();){
    size_t j=i; while(j<e.size() && e[j].w==e[i].w) j++;
    // Collect useful edges (connecting different DSU comps)
    vector<Edge> g; g.reserve(j-i);
    for(size_t k=i;k<j;++k){ int a=d.f(e[k].u), b=d.f(e[k].v); if(a!=b) g.push_back({a,b,e[k].w,e[k].id}); }
    // Build compact graph of components
    unordered_map<int,int> idx; idx.reserve(g.size()*2);
    for(auto &E: g){ if(!idx.count(E.u)) idx[E.u]=idx.size(); if(!idx.count(E.v)) idx[E.v]=idx.size(); }
    int m = idx.size(); vector<vector<pair<int,int>>> adj(m); // to, original edge id (from g)
    for(auto &E: g){ int a=idx[E.u], b=idx[E.v]; adj[a].push_back({b,E.id}); adj[b].push_back({a,E.id}); }
    // Bridges on this graph
    vector<int> tin(m,-1), low(m,0), pe(m,-1); int timer=0;
    function<void(int,int)> dfs=[&](int v,int p){ tin[v]=low[v]=++timer; for(auto [to, eid]: adj[v]) if(to!=p){ if(tin[to]==-1){ pe[to]=eid; dfs(to,v); low[v]=min(low[v], low[to]); if(low[to] > tin[v]){ // bridge
            // mark original edge id as critical
            auto it = find_if(g.begin(), g.end(), [&](const Edge& E){ return E.id==eid; });
            if(it!=g.end()) critical[it->id]=1;
          } } else low[v]=min(low[v], tin[to]); }
    };
    for(int v=0; v<m; ++v) if(tin[v]==-1) dfs(v,-1);
    // Union original DSU by this weight group
    for(size_t k=i;k<j;++k) d.u(e[k].u, e[k].v);
    i=j;
  }
  return critical;
}

