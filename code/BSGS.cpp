/*
  Baby-Step Giant-Step for discrete log: solve a^x = b (mod m) for x
  - Works when gcd(a,m)=1
*/

#include <bits/stdc++.h>
using namespace std; using u64=unsigned long long; using u128=unsigned __int128;

inline u64 mul(u64 a,u64 b,u64 m){ return (u128)a*b % m; }
inline u64 pw(u64 a,u64 e,u64 m){ u64 r=1%m; while(e){ if(e&1) r=mul(r,a,m); a=mul(a,a,m); e>>=1; } return r; }

long long bsgs(u64 a, u64 b, u64 m){ a%=m; b%=m; if(b==1% m) return 0; int n = (int)ceil(sqrt((long double)m)); unordered_map<u64,int> table; u64 e=1; for(int j=0;j<n;++j){ if(!table.count(e)) table[e]=j; e=mul(e,a,m); }
  u64 an = pw(a, n, m), inv = 0; // compute a^{-n}
  // Fermat does not apply; use extended Euclid via Euler's theorem: assume gcd(a,m)=1
  // find inverse of an by binary exponent using Euler's totient unknown: fallback to extended Euclid is complex for general m
  // We can compute inv = a^{-n} mod m via pow(a, phi(m)-n, m) if phi known; instead use baby steps on inverse: precompute an_inv by Euler or use long double trick not safe
  // Here, use pow with Euler's theorem assumption if m is prime-like; otherwise require precomputed inverse
  // For generic, we can compute inverse via extended algorithm on 64-bit using standard EGCD:
  auto egcd=[&](auto self, long long x, long long y)->pair<long long,long long>{ if(y==0) return {1,0}; auto pr=self(self,y,x%y); return make_pair(pr.second, pr.first - (x/y)*pr.second); };
  long long x,y; tie(x,y)=egcd(egcd, (long long)an, (long long)m); long long g = (long long)std::gcd((long long)an,(long long)m); if(g!=1) return -1; inv = (x%m + m)%m;
  u64 cur=b; for(int i=0;i<=n;++i){ auto it=table.find(cur); if(it!=table.end()){ long long ans = (long long)i*n + it->second; return ans; } cur = mul(cur, inv, m); }
  return -1;
}

