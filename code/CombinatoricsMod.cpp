/*
  Combinatorics modulo prime: factorials, inverse factorials, nCr
  - Precompute up to N in O(N)
*/

#include <bits/stdc++.h>
using namespace std;

struct CombMod {
  int N; long long MOD; vector<long long> fact, invfact;
  long long modpow(long long a, long long e){ long long r=1%MOD; while(e){ if(e&1) r=r*a%MOD; a=a*a%MOD; e>>=1;} return r; }
  CombMod(int N=0, long long MOD=1000000007LL){ init(N, MOD); }
  void init(int N_, long long MOD_){ N=N_; MOD=MOD_; fact.assign(N+1,1); invfact.assign(N+1,1); for(int i=1;i<=N;++i) fact[i]=fact[i-1]*i%MOD; invfact[N]=modpow(fact[N], MOD-2); for(int i=N;i>0;--i) invfact[i-1]=invfact[i]*i%MOD; }
  long long nCr(int n, int r){ if(r<0||r>n) return 0; return fact[n]*invfact[r]%MOD*invfact[n-r]%MOD; }
};

