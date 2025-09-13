/*
  Inclusion-Exclusion templates
  - count_not_divisible(N, primes): count integers in [1..N] not divisible by any prime in list
  - generic_inclusion_exclusion(cnt[]): given counts of elements belonging to each subset size k,
    returns sum_{k} (-1)^k * cnt[k] (useful when precomputed overlaps are available)
*/

#include <bits/stdc++.h>
using namespace std;

long long count_not_divisible(long long N, const vector<long long>& p){
  int m = (int)p.size(); long long ans = 0;
  for (int mask = 1; mask < (1<<m); ++mask){
    __int128 mult = 1; int bits = 0; bool overflow=false;
    for (int i=0;i<m;++i) if (mask & (1<<i)){
      ++bits; mult = mult / std::gcd((long long)mult, p[i]) * p[i];
      if (mult > N) { overflow=true; break; }
    }
    if (overflow || mult==0) continue;
    long long add = (long long)(N / (long long)mult);
    if (bits & 1) ans += add; else ans -= add;
  }
  return N - ans;
}

long long inclusion_exclusion_from_counts(const vector<long long>& cnt){
  long long s = 0; for (size_t k=0;k<cnt.size();++k) s += (k%2? -cnt[k] : cnt[k]); return s; }

// Example usage:
// int main(){
//   cout << count_not_divisible(100, {2,3,5}) << "\n"; // numbers not divisible by 2,3,5
// }

