/*
  Held-Karp TSP with path reconstruction (O(n^2 2^n))
*/

#include <bits/stdc++.h>
using namespace std;

pair<long long, vector<int>> tsp_held_karp(const vector<vector<long long>>& d){
  int n=d.size(); int N=1<<n; const long long INF=(1LL<<60);
  vector<vector<long long>> dp(N, vector<long long>(n, INF));
  vector<vector<int>> par(N, vector<int>(n, -1));
  dp[1][0]=0;
  for(int m=1;m<N;++m){ if(!(m&1)) continue; for(int i=0;i<n;++i){ if(!(m&(1<<i))||dp[m][i]>=INF) continue; int rem=((~m)&(N-1)); for(int j=rem;j;j&=j-1){ int k=__builtin_ctz(j); int m2=m|(1<<k); long long nd=dp[m][i]+d[i][k]; if(nd<dp[m2][k]){ dp[m2][k]=nd; par[m2][k]=i; } } } }
  long long best=INF; int last=-1; int full=N-1; for(int i=0;i<n;++i){ long long val=dp[full][i]+d[i][0]; if(val<best){ best=val; last=i; } }
  vector<int> path; int m=full, cur=last; while(cur!=-1){ path.push_back(cur); int p=par[m][cur]; m^=(1<<cur); cur=p; } reverse(path.begin(), path.end()); path.push_back(0);
  return {best, path};
}

