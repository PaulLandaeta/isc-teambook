/*
  Sqrt Decomposition (block decomposition) for range sum + point update
  - build(a), update(idx, delta), query(l,r) [l,r)
*/

#include <bits/stdc++.h>
using namespace std;

struct SqrtDecomp {
  int n, B, NB; vector<long long> a, blk;
  SqrtDecomp(int n=0){ if(n) init(n); }
  void init(int n_){ n=n_; B=max(1,(int)sqrt(n)); NB=(n+B-1)/B; a.assign(n,0); blk.assign(NB,0); }
  void build(const vector<long long>& v){ init((int)v.size()); a=v; fill(blk.begin(),blk.end(),0); for(int i=0;i<n;++i) blk[i/B]+=a[i]; }
  void update(int idx,long long delta){ blk[idx/B]+=delta; a[idx]+=delta; }
  long long query(int l,int r){ long long s=0; int i=l; while(i<r && i%B) s+=a[i++]; while(i+B<=r){ s+=blk[i/B]; i+=B; } while(i<r) s+=a[i++]; return s; }
};

