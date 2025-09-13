/*
  Chinese Remainder Theorem (CRT) and Garner's algorithm
  - crt_merge(a1, m1, a2, m2): merge x == a1 (mod m1), x == a2 (mod m2)
    Works for non-coprime moduli. Returns {a, m} with x == a (mod m), or {-1, -1} if no solution.
  - crt(rems, mods): merge lists (possibly non-coprime). Returns {a, m}.
  - garner(rems, mods, MOD): assume mods are pairwise coprime. Computes x == ai (mod mi) and returns x mod MOD.
    If MOD=0, returns x as 128-bit accumulated into unsigned long long when it fits (use with care).
*/

#include <bits/stdc++.h>
using namespace std;
using i64 = long long; using u64 = unsigned long long; using u128 = unsigned __int128;

i64 egcd(i64 a, i64 b, i64 &x, i64 &y){ if(!b){ x=(a>=0?1:-1); y=0; return llabs(a);} i64 x1,y1; i64 g=egcd(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g; }

pair<i64,i64> crt_merge(i64 a1, i64 m1, i64 a2, i64 m2){
  // merge into x == a1 (mod m1), x == a2 (mod m2)
  if (m1 < 0) m1 = -m1; if (m2 < 0) m2 = -m2;
  a1 %= m1; if (a1 < 0) a1 += m1; a2 %= m2; if (a2 < 0) a2 += m2;
  i64 x, y; i64 g = egcd(m1, m2, x, y);
  if ((a2 - a1) % g != 0) return {-1, -1}; // no solution
  __int128 lcm = (__int128)m1 / g * m2;
  __int128 k = (__int128)(a2 - a1) / g * x; // k may be negative
  i64 mod2g = m2 / g;
  i64 kmod = (i64)((k % mod2g + mod2g) % mod2g);
  __int128 res = ( (__int128)a1 + (__int128)m1 * kmod ) % lcm;
  i64 R = (i64)(res < 0 ? res + lcm : res);
  i64 M = (i64)lcm;
  return {R, M};
}

pair<i64,i64> crt(const vector<i64>& a, const vector<i64>& m){
  i64 R = 0, M = 1; // x == 0 (mod 1)
  for (size_t i=0;i<a.size();++i){ auto t = crt_merge(R, M, a[i], m[i]); if (t.second == -1) return {-1,-1}; R = t.first; M = t.second; }
  return {R, M};
}

u64 modmul_u128(u64 a, u64 b, u64 m){ return (u128)a*b % m; }

u64 modpow_u128(u64 a, u64 e, u64 m){ u64 r=1%m; while(e){ if(e&1) r=modmul_u128(r,a,m); a=modmul_u128(a,a,m); e>>=1;} return r; }

u64 inv_mod_u64(u64 a, u64 m){ // assumes gcd(a,m)=1 and m fits in 64-bit
  long long x, y; long long g = egcd((long long)a, (long long)m, x, y); if(g!=1 && g!=-1) return 0; long long inv = x % (long long)m; if(inv<0) inv += (long long)m; return (u64)inv;
}

u64 garner(const vector<u64>& a, const vector<u64>& m, u64 MOD){
  // assumes pairwise coprime m[i]
  size_t n = a.size();
  vector<u64> coeff(n+1, 1), consts(n+1, 0);
  vector<u64> mm = m; // extend with MOD if provided
  if (MOD) mm.push_back(MOD);
  for (size_t k=0; k<n; ++k){
    u64 t = (a[k] + mm[k] - consts[k] % mm[k]) % mm[k];
    u64 inv = inv_mod_u64(coeff[k] % mm[k], mm[k]);
    u64 x = (u128)t * inv % mm[k];
    for (size_t i=k+1; i<mm.size(); ++i){
      consts[i] = (consts[i] + (u128)coeff[i] * x) % mm[i];
      coeff[i] = (u128)coeff[i] * mm[k] % mm[i];
    }
  }
  return MOD ? consts.back() % MOD : consts[n];
}

// Example usage:
// int main(){
//   // General CRT (non-coprime)
//   auto r = crt({2, 3, 2}, {3, 5, 7}); // 23 mod 105
//   cout << r.first << " " << r.second << "\n";
//   // Garner (pairwise coprime)
//   cout << garner({2,3,2}, {3,5,7}, 1000000007ULL) << "\n"; // 23
// }
