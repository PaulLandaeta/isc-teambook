/*
  Sieve of Eratosthenes (linear) with smallest prime factor (SPF)
  - Time: O(n)
  - Memory: O(n)
  Provides:
    - primes: list of primes up to n
    - spf[x]: smallest prime factor of x (x>=2), or 0 if x<2
    - is_prime(x): quick primality for x<=n
    - factorize(x): factorization for x<=n using spf
*/

#include <bits/stdc++.h>
using namespace std;

struct Sieve {
  int n; vector<int> primes, spf; vector<char> comp;
  Sieve(int n=0) { init(n); }
  void init(int n_) {
    n = n_; primes.clear(); spf.assign(n+1, 0); comp.assign(n+1, 0);
    for (int i = 2; i <= n; ++i) {
      if (!comp[i]) { primes.push_back(i); spf[i] = i; }
      for (int p : primes) {
        long long x = 1LL * p * i; if (x > n) break;
        comp[x] = 1; spf[x] = p;
        if (i % p == 0) break;
      }
    }
  }
  bool is_prime(int x) const { return x >= 2 && x <= n && !comp[x]; }
  vector<pair<int,int>> factorize(int x) const {
    vector<pair<int,int>> f; if (x < 2) return f;
    while (x > 1) {
      int p = spf[x], c = 0; while (x % p == 0) { x /= p; ++c; }
      f.push_back({p, c});
    }
    return f;
  }
};

// Example usage:
// int main(){ Sieve sv(1000000); cout << sv.primes.size() << "\n"; }

