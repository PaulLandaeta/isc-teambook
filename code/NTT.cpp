/*
  Number Theoretic Transform (NTT)
  - Works over mod 998244353 with primitive root 3
  - convolution(a,b) returns c = a * b under mod
*/

#include <bits/stdc++.h>
using namespace std;

const uint32_t MOD = 998244353; const uint32_t G = 3;

uint32_t mod_pow(uint32_t a, uint32_t e){ uint64_t r=1; while(e){ if(e&1) r=r*a%MOD; a=(uint64_t)a*a%MOD; e>>=1;} return (uint32_t)r; }

void ntt(vector<uint32_t>& a, bool invert){ int n=a.size(); static vector<int> rev; static vector<uint32_t> roots{0,1}; if((int)rev.size()!=n){ int k=__builtin_ctz(n); rev.assign(n,0); for(int i=0;i<n;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1)); }
  if((int)roots.size()<n){ int k=__builtin_ctz(roots.size()); roots.resize(n); while((1<<k)<n){ uint32_t z = mod_pow(G, (MOD-1)>>(k+1)); for(int i=1<<(k-1); i<(1<<k); ++i){ roots[2*i]=roots[i]; roots[2*i+1]=(uint64_t)roots[i]*z%MOD; } ++k; } }
  for(int i=0;i<n;++i) if(i<rev[i]) swap(a[i], a[rev[i]]);
  for(int len=1; len<n; len<<=1){ for(int i=0;i<n;i+=2*len){ for(int j=0;j<len;++j){ uint32_t u=a[i+j]; uint32_t v=(uint64_t)a[i+j+len]*roots[len+j]%MOD; a[i+j]=u+v; if(a[i+j]>=MOD) a[i+j]-=MOD; a[i+j+len]=u+MOD-v; if(a[i+j+len]>=MOD) a[i+j+len]-=MOD; } } }
  if(invert){ reverse(a.begin()+1, a.end()); uint32_t inv_n = mod_pow(n, MOD-2); for(uint32_t &x: a) x=(uint64_t)x*inv_n%MOD; }
}

vector<uint32_t> convolution(const vector<uint32_t>& A, const vector<uint32_t>& B){ vector<uint32_t> a(A.begin(),A.end()), b(B.begin(),B.end()); int n=1; while(n<(int)a.size()+(int)b.size()-1) n<<=1; a.resize(n); b.resize(n); ntt(a,false); ntt(b,false); for(int i=0;i<n;++i) a[i]=(uint64_t)a[i]*b[i]%MOD; ntt(a,true); a.resize(A.size()+B.size()-1); return a; }

