/*
  Karp's algorithm for minimum mean cycle in directed graph
  - min_mean_cycle(n, edges): returns minimum mean weight (as double)
*/

#include <bits/stdc++.h>
using namespace std;

struct E { int u,v; long long w; };

double min_mean_cycle(int n, const vector<E>& edges){
  const long long INF = (1LL<<60);
  vector<vector<long long>> dp(n+1, vector<long long>(n, INF));
  for(int v=0; v<n; ++v) dp[0][v]=0;
  for(int k=1;k<=n;++k){
    for(int v=0; v<n; ++v) dp[k][v]=INF;
    for(auto &e: edges){ if(dp[k-1][e.u]<INF) dp[k][e.v] = min(dp[k][e.v], dp[k-1][e.u] + e.w); }
  }
  double ans = 1e300;
  for(int v=0; v<n; ++v){ if(dp[n][v]==INF) continue; double mx = -1e300; for(int k=0;k<n;++k){ if(dp[k][v]==INF) continue; mx = max(mx, (dp[n][v]-dp[k][v]) / double(n-k)); } ans = min(ans, mx); }
  return ans;
}

