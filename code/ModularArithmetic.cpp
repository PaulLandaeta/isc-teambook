/*
  Modular arithmetic utilities (64-bit)
  - mul_mod(a,b,m): (a*b) % m using __int128 (safe for m < 2^64)
  - pow_mod(a,e,m): a^e % m (binary exponentiation)
  - egcd(a,b): extended gcd, returns g and x,y with ax+by=g
  - inv_mod(a,m): modular inverse of a mod m (requires gcd(a,m)=1)
  - inv_mod_prime(a,p): inverse modulo prime p via Fermat's little theorem
*/

#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using i64 = long long;
using u128 = unsigned __int128;

inline u64 mul_mod(u64 a, u64 b, u64 m) {
  return (u128)a * b % m;
}

inline u64 pow_mod(u64 a, u64 e, u64 m) {
  u64 r = 1 % m;
  while (e) {
    if (e & 1) r = mul_mod(r, a, m);
    a = mul_mod(a, a, m);
    e >>= 1;
  }
  return r;
}

i64 egcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) { x = (a >= 0 ? 1 : -1); y = 0; return llabs(a); }
  i64 x1, y1; i64 g = egcd(b, a % b, x1, y1);
  x = y1; y = x1 - (a / b) * y1; return g;
}

i64 inv_mod(i64 a, i64 m) {
  i64 x, y; i64 g = egcd(a, m, x, y);
  if (g != 1 && g != -1) return -1; // no inverse
  i64 inv = x % m; if (inv < 0) inv += m; return inv;
}

u64 inv_mod_prime(u64 a, u64 p) { // p must be prime and a % p != 0
  return pow_mod(a % p, p - 2, p);
}

// Example usage:
// int main(){
//   cout << pow_mod(2, 100, 1000000007ULL) << "\n"; // fast exp
//   cout << inv_mod(3, 11) << "\n"; // 4
// }

