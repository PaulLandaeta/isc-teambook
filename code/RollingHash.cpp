/*
  Rolling Hash (polynomial) with double mod
  - Precompute prefix hashes and powers; query substring hashes in O(1)
  - Suitable for equality checks, palindrome checks (with reverse), etc.
*/

#include <bits/stdc++.h>
using namespace std;

struct RollingHash {
  using ull = unsigned long long;
  static const ull M1 = 1000000007ULL, M2 = 1000000009ULL;
  static const ull B = 911382323ULL; // base
  int n;
  vector<ull> p1, p2, h1, h2;
  RollingHash() {}
  RollingHash(const string& s) { build(s); }
  void build(const string& s) {
    n = (int)s.size();
    p1.assign(n + 1, 1); p2.assign(n + 1, 1);
    h1.assign(n + 1, 0); h2.assign(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      p1[i + 1] = (p1[i] * B) % M1;
      p2[i + 1] = (p2[i] * B) % M2;
      h1[i + 1] = (h1[i] * B + (unsigned char)s[i] + 1) % M1;
      h2[i + 1] = (h2[i] * B + (unsigned char)s[i] + 1) % M2;
    }
  }
  pair<ull, ull> get(int l, int r) const { // [l, r)
    ull x1 = (h1[r] + M1 - (h1[l] * p1[r - l]) % M1) % M1;
    ull x2 = (h2[r] + M2 - (h2[l] * p2[r - l]) % M2) % M2;
    return {x1, x2};
  }
};

