/*
  Bitmask Tricks and SOS DP
  - Iterate set bits, submasks, supersets
  - Helpers: lsb, msb, popcount wrappers
  - SOS DP (Sum Over Subsets):
      Given f[mask], computes F[mask] = sum_{s subset of mask} f[s]
    and the supersets variant:
      G[mask] = sum_{s superset of mask} f[s]
*/

#include <bits/stdc++.h>
using namespace std;

// popcount wrappers
inline int popcount32(unsigned int x){
#if defined(__GNUG__) || defined(__clang__)
  return __builtin_popcount(x);
#else
  int c=0; while(x){ x&=x-1; ++c; } return c;
#endif
}
inline int popcount64(unsigned long long x){
#if defined(__GNUG__) || defined(__clang__)
  return __builtin_popcountll(x);
#else
  int c=0; while(x){ x&=x-1; ++c; } return c;
#endif
}

// least significant bit index (0-based), x>0
inline int lsb_index(unsigned int x){ return __builtin_ctz(x); }
// most significant bit index (0-based), x>0
inline int msb_index(unsigned int x){ return 31 - __builtin_clz(x); }

// Iterate all set bit positions in mask
// for(int b : bits(mask)) { ... }
inline vector<int> bits(unsigned int m){ vector<int> res; while(m){ int b = __builtin_ctz(m); res.push_back(b); m &= m-1; } return res; }

// Iterate all submasks of m (including 0 and m)
// for (int s = m; ; s = (s-1) & m) { ... if (s == 0) break; }

// Iterate all supersets of m within universe [0..(1<<n)-1]
// for (int s = m; s < (1<<n); s = (s+1) | m) { ... }

// SOS DP: sums over subsets
// In-place transforms. N must be a power of two.
// After sos_subset(F), F[mask] = sum_{s subset of mask} F[s]_original
void sos_subset(vector<long long>& F){
  int N = (int)F.size(); int n = 31 - __builtin_clz(N);
  for(int i=0;i<n;++i){
    for(int mask=0; mask<N; ++mask){ if(mask & (1<<i)) F[mask] += F[mask^(1<<i)]; }
  }
}

// Supersets version: After sos_superset(F), F[mask] = sum_{s superset of mask} F[s]_original
void sos_superset(vector<long long>& F){
  int N = (int)F.size(); int n = 31 - __builtin_clz(N);
  for(int i=0;i<n;++i){
    for(int mask=0; mask<N; ++mask){ if((mask & (1<<i)) == 0) F[mask] += F[mask | (1<<i)]; }
  }
}

// Example usage (commented):
// int main(){
//   int n=3; int N=1<<n; vector<long long> f(N,1);
//   sos_subset(f); // now f[mask] = 2^{popcount(mask)}
// }

