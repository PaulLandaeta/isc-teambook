/*
  Subset Zeta/Mobius (inverse SOS) and Subset Convolution
  - zeta_subset(f): F[mask] = sum_{s subset of mask} f[s]
  - mobius_subset(F): inverse of zeta (restores f)
  - subset_convolution(f,g): h[S] = sum_{A+B=S, A cap B = empty} f[A]*g[B]
    Complexity: O(n^2 2^n)
*/

#include <bits/stdc++.h>
using namespace std;

void zeta_subset(vector<long long>& F){ int N=F.size(); int n=31-__builtin_clz(N); for(int i=0;i<n;++i) for(int m=0;m<N;++m) if(m&(1<<i)) F[m]+=F[m^(1<<i)]; }
void mobius_subset(vector<long long>& F){ int N=F.size(); int n=31-__builtin_clz(N); for(int i=0;i<n;++i) for(int m=0;m<N;++m) if(m&(1<<i)) F[m]-=F[m^(1<<i)]; }

vector<long long> subset_convolution(const vector<long long>& f, const vector<long long>& g){
  int N=f.size(); int n=0; while((1<<n)<N) ++n; vector<vector<long long>> F(n+1, vector<long long>(N,0)), G(n+1, vector<long long>(N,0));
  for(int m=0;m<N;++m){ int k=__builtin_popcount((unsigned)m); F[k][m]=f[m]; G[k][m]=g[m]; }
  for(int k=0;k<=n;++k){ zeta_subset(F[k]); zeta_subset(G[k]); }
  vector<vector<long long>> H(n+1, vector<long long>(N,0));
  for(int m=0;m<N;++m){ for(int k=0;k<=n;++k){ long long s=0; for(int i=0;i<=k;++i) s += F[i][m]*G[k-i][m]; H[k][m]=s; } }
  for(int k=0;k<=n;++k) mobius_subset(H[k]);
  vector<long long> h(N,0); for(int m=0;m<N;++m){ int k=__builtin_popcount((unsigned)m); h[m]=H[k][m]; }
  return h;
}

