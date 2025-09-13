/*
  Title: Eulerian Path/Circuit (Hierholzer)
  Complexity: O(E)
  Description: Finds an Eulerian path/circuit in an undirected graph if it exists.
  Example:
  // int main(){
  //   int n=3; vector<vector<pair<int,int>>> adj(n);
  //   auto add=[&](int u,int v,int id){ adj[u].push_back({v,id}); adj[v].push_back({u,id}); };
  //   add(0,1,0); add(1,2,1); add(2,0,2);
  //   auto path = euler_undirected(n, adj); // path of vertices, size E+1
  // }
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> euler_undirected(int n, const vector<vector<pair<int,int>>>& adj){
  int m=0; for(int u=0;u<n;++u) m += adj[u].size(); if(m%2) return {}; m/=2;
  vector<int> deg(n,0); for(int u=0;u<n;++u) deg[u]=adj[u].size();
  int start = 0, odd=0; for(int i=0;i<n;++i) if(deg[i]%2){ odd++; start=i; }
  if(!(odd==0 || odd==2)) return {};
  vector<char> used(m,0); vector<int> it(n,0), st; vector<int> path;
  st.push_back(start);
  vector<vector<pair<int,int>>> g = adj;
  while(!st.empty()){
    int u=st.back();
    while(it[u] < (int)g[u].size() && used[g[u][it[u]].second]) ++it[u];
    if(it[u] == (int)g[u].size()){ path.push_back(u); st.pop_back(); }
    else { auto [v,id]=g[u][it[u]++]; used[id]=1; st.push_back(v); }
  }
  if((int)path.size()!=m+1) return {}; reverse(path.begin(), path.end()); return path;
}
