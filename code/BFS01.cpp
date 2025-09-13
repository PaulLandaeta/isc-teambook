/*
  0-1 BFS on graph with edge weights in {0,1}
  - Computes shortest distances in O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> bfs01(int n, const vector<vector<pair<int,int>>>& adj, int s) {
  const int INF = 1e9; deque<int> dq; vector<int> dist(n, INF); dist[s]=0; dq.push_front(s);
  while(!dq.empty()){
    int u=dq.front(); dq.pop_front();
    for(auto [v,w]: adj[u]){
      int nd = dist[u] + (w?1:0);
      if(nd < dist[v]){ dist[v]=nd; if(w) dq.push_back(v); else dq.push_front(v);}    
    }
  }
  return dist;
}

