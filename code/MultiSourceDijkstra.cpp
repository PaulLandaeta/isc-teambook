/*
  Multi-source Dijkstra: initialize with multiple sources at distance 0
*/

#include <bits/stdc++.h>
using namespace std;

vector<long long> multi_source_dijkstra(int n, const vector<vector<pair<int,long long>>>& adj, const vector<int>& sources){
  const long long INF=(1LL<<60); vector<long long> d(n,INF); priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
  for(int s: sources){ d[s]=0; pq.push({0,s}); }
  while(!pq.empty()){
    auto [du,u]=pq.top(); pq.pop(); if(du!=d[u]) continue; for(auto [v,w]: adj[u]) if(du+w < d[v]) d[v]=du+w, pq.push({d[v],v});
  }
  return d;
}

