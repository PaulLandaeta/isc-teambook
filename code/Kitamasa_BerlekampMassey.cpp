/*
  Berlekamp-Massey to find linear recurrence from sequence, and Kitamasa to compute n-th term
*/

#include <bits/stdc++.h>
using namespace std; const long long MOD=1000000007LL;

vector<long long> berlekamp_massey(const vector<long long>& s){ vector<long long> C(1,1), B(1,1); int L=0, m=1; long long b=1; for(size_t n=0;n<s.size();++n){ long long d=0; for(int i=0;i<=L;++i) d=(d + C[i]*s[n-i])%MOD; if(d==0){ ++m; } else if(2*L <= (int)n){ auto T=C; long long coef = d * 1LL * (long long)pow(b, MOD-2) % MOD; C.resize(max(C.size(), B.size()+m)); for(size_t i=0;i<B.size();++i) C[i+m] = (C[i+m] - coef*B[i])%MOD; L = (int)n+1 - L; B=T; b=d; m=1; } else { long long coef = d * 1LL * (long long)pow(b, MOD-2) % MOD; C.resize(max(C.size(), B.size()+m)); for(size_t i=0;i<B.size();++i) C[i+m] = (C[i+m] - coef*B[i])%MOD; ++m; } } for(auto &x:C) x=(x%MOD+MOD)%MOD; C.erase(C.begin()); for(auto &x:C) x=(MOD - x)%MOD; return C; }

vector<long long> combine(const vector<long long>& a, const vector<long long>& b, const vector<long long>& rec){ int k=rec.size(); vector<long long> res(2*k+1,0); for(int i=0;i<k;++i) for(int j=0;j<k;++j) res[i+j]=(res[i+j]+a[i]*b[j])%MOD; for(int i=2*k-1;i>=k;--i){ for(int j=1;j<=k;++j) res[i-j]=(res[i-j]+res[i]*rec[j-1])%MOD; } res.resize(k); return res; }

long long kitamasa(vector<long long> rec, vector<long long> init, long long n){ int k=rec.size(); if(n<(int)init.size()) return init[n]%MOD; vector<long long> pol(k), e(k); pol[0]=1; e[1%k]=1; while(n){ if(n&1) pol=combine(pol,e,rec); e=combine(e,e,rec); n>>=1; } long long ans=0; for(int i=0;i<k;++i) ans=(ans+pol[i]*init[i])%MOD; return ans; }

