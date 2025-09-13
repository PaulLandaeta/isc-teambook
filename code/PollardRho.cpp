/*
  Miller-Rabin + Pollard-Rho for 64-bit factorization
*/

#include <bits/stdc++.h>
using namespace std; using u128 = unsigned __int128; using u64 = unsigned long long; using u32 = unsigned int;

inline u64 mul(u64 a,u64 b,u64 m){ return (u128)a*b % m; }
inline u64 pw(u64 a,u64 e,u64 m){ u64 r=1%m; while(e){ if(e&1) r=mul(r,a,m); a=mul(a,a,m); e>>=1; } return r; }
bool isPrime(u64 n){ if(n<2) return false; for(u64 p:{2,3,5,7,11,13,17,19,23,29,31,37}){ if(n%p==0) return n==p; } u64 d=n-1,s=0; while((d&1)==0){ d>>=1; ++s; } auto check=[&](u64 a){ if(a%(n)==0) return true; u64 x=pw(a,d,n); if(x==1||x==n-1) return true; for(u64 r=1;r<s;++r){ x=mul(x,x,n); if(x==n-1) return true; } return false; }; for(u64 a:{2,325,9375,28178,450775,9780504,1795265022}) if(!check(a)) return false; return true; }
u64 f(u64 x,u64 c,u64 mod){ return (mul(x,x,mod)+c)%mod; }
u64 rho(u64 n){ if((n&1)==0) return 2; std::mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); while(true){ u64 x=uniform_int_distribution<u64>(2,n-2)(rng), y=x, c=uniform_int_distribution<u64>(1,n-1)(rng), d=1; while(d==1){ x=f(x,c,n); y=f(f(y,c,n),c,n); u64 diff = x>y? x-y: y-x; d=std::gcd(diff, n); if(d==n) break; } if(d>1&&d<n) return d; }
}
void factor(u64 n, map<u64,int>& res){ if(n==1) return; if(isPrime(n)){ res[n]++; return; } u64 d=rho(n); factor(d,res); factor(n/d,res); }

