/*
  Bitmask DP templates and utilities
  - Iterate subsets of a mask
  - Count bits (popcount) portable wrapper
  - TSP DP example (O(n^2 2^n))
*/

#include <bits/stdc++.h>
using namespace std;

// Iterate all submasks of mask (including 0 and mask)
// for (int s = m; ; s = (s - 1) & m) { ... if (s == 0) break; }

inline int popcount32(unsigned int x) {
#if defined(__GNUG__) || defined(__clang__)
  return __builtin_popcount(x);
#else
  // fallback
  int c = 0; while (x) { x &= x - 1; ++c; } return c;
#endif
}

// Travelling Salesman Problem (TSP) DP on bitmask
// dist is n x n (long long), dp[mask][i]: min cost to visit mask and end at i
long long tsp_bitmask_dp(const vector<vector<long long>>& dist) {
  const long long INF = (1LL<<60);
  int n = (int)dist.size();
  int N = 1 << n;
  vector<vector<long long>> dp(N, vector<long long>(n, INF));
  dp[1][0] = 0; // start at 0 (mask with only bit 0)
  for (int m = 1; m < N; ++m) {
    for (int i = 0; i < n; ++i) if (dp[m][i] < INF && (m & (1 << i))) {
      int rem = ((~m) & (N - 1));
      for (int j = rem; j; j &= (j - 1)) {
        int k = __builtin_ctz(j); // next not visited node
        int m2 = m | (1 << k);
        dp[m2][k] = min(dp[m2][k], dp[m][i] + dist[i][k]);
      }
    }
  }
  long long ans = INF;
  for (int i = 0; i < n; ++i) ans = min(ans, dp[N - 1][i] + dist[i][0]);
  return ans;
}

// Example usage:
// int main(){
//   vector<vector<long long>> d = {{0,10,15,20},{10,0,35,25},{15,35,0,30},{20,25,30,0}};
//   cout << tsp_bitmask_dp(d) << "\n"; // 80
// }

