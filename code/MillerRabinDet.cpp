/*
  Deterministic Miller-Rabin for 64-bit integers
  - Time: ~ O(k log^3 n) with fixed bases (k small)
  - For 0 <= n < 2^64, the set of bases {2,3,5,7,11,13,17} is deterministic
*/

#include <bits/stdc++.h>
using namespace std;

using u128 = unsigned __int128;
using u64 = unsigned long long;
using u32 = unsigned int;

inline u64 mul_mod(u64 a, u64 b, u64 m) {
  return (u128)a * b % m;
}
inline u64 pow_mod(u64 a, u64 e, u64 m) {
  u64 r = 1;
  while (e) { if (e & 1) r = mul_mod(r, a, m); a = mul_mod(a, a, m); e >>= 1; }
  return r;
}

bool isPrime64(u64 n) {
  if (n < 2) return false;
  for (u64 p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL}) {
    if (n % p == 0) return n == p;
  }
  u64 d = n - 1, s = 0;
  while ((d & 1) == 0) { d >>= 1; ++s; }
  auto check = [&](u64 a)->bool{
    u64 x = pow_mod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (u64 r = 1; r < s; ++r) {
      x = mul_mod(x, x, n);
      if (x == n - 1) return true;
    }
    return false;
  };
  for (u64 a : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL}) if (!check(a)) return false;
  return true;
}

// Example usage:
// int main(){ cout << isPrime64(1000000007ULL) << "\n"; }
