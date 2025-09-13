/*
  Segmented Sieve of Eratosthenes
  - Lists primes in an arbitrary interval [L, R] (0 <= L <= R <= 1e18 typical)
  - Uses a simple sieve up to sqrt(R), then marks composites in the segment
  - Memory: O(R-L+1)

  Interface:
    vector<long long> segmented_sieve(long long L, long long R)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> simple_sieve(int n) {
  int m = max(2, n);
  vector<char> comp(m + 1, 0);
  vector<int> primes;
  for (int i = 2; 1LL * i * i <= m; ++i)
    if (!comp[i]) for (long long j = 1LL * i * i; j <= m; j += i) comp[(int)j] = 1;
  for (int i = 2; i <= m; ++i) if (!comp[i]) primes.push_back(i);
  return primes;
}

vector<long long> segmented_sieve(long long L, long long R) {
  if (R < 2 || L > R) return {};
  long long s = floor(sqrt((long double)R));
  vector<int> base = simple_sieve((int)s);
  long long len = R - L + 1;
  vector<char> comp(len, 0);

  for (int p : base) {
    long long start = max(1LL * p * p, ((L + p - 1) / p) * 1LL * p);
    for (long long x = start; x <= R; x += p) comp[(int)(x - L)] = 1;
  }

  vector<long long> res;
  for (long long x = max(2LL, L); x <= R; ++x)
    if (!comp[(int)(x - L)]) res.push_back(x);
  return res;
}

// Example usage:
// int main(){
//   auto ps = segmented_sieve(1, 100);
//   for (auto p: ps) cout << p << ' ';
//   cout << "\n";
// }

