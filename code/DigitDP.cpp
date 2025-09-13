/*
  Digit DP templates
  - count_sum_divisible(R, mod): count x in [0, R] such that sum of digits(x) % mod == 0
  - count_sum_divisible(L, R, mod): count x in [L, R] with same property

  Notes:
  - Works for 0 <= R up to 10^18 (or longer if you pass a longer string)
  - Complexity: O(len * mod * 10)
*/

#include <bits/stdc++.h>
using namespace std;

long long solve_sum_divisible(const string &s, int mod) {
  int n = (int)s.size();
  // dp[pos][sum_mod][tight][started]
  vector dp(n + 1, vector(mod, array<array<long long, 2>, 2>{}));
  vector vis(n + 1, vector(mod, array<array<char, 2>, 2>{}));

  function<long long(int,int,int,int)> dfs = [&](int pos, int sum, int tight, int started) -> long long {
    if (pos == n) return started ? (sum % mod == 0) : 1; // treat 0 as valid (sum 0)
    if (vis[pos][sum][tight][started]) return dp[pos][sum][tight][started];
    vis[pos][sum][tight][started] = 1;
    int limit = tight ? (s[pos] - '0') : 9;
    long long res = 0;
    for (int d = 0; d <= limit; ++d) {
      int ntight = tight && (d == limit);
      int nstarted = started || (d != 0);
      int nsum = sum;
      if (nstarted) nsum = (nsum + d) % mod;
      else nsum = 0; // still leading zeros -> sum stays 0
      res += dfs(pos + 1, nsum, ntight, nstarted);
    }
    return dp[pos][sum][tight][started] = res;
  };

  return dfs(0, 0, 1, 0);
}

long long count_sum_divisible(long long R, int mod) {
  if (R < 0) return 0;
  string s = to_string(R);
  return solve_sum_divisible(s, mod);
}

long long count_sum_divisible(long long L, long long R, int mod) {
  if (L > R) return 0;
  return count_sum_divisible(R, mod) - count_sum_divisible(L - 1, mod);
}

// Example usage:
// int main(){
//   // Count numbers in [1, 1000] whose sum of digits is divisible by 3
//   cout << count_sum_divisible(1, 1000, 3) << "\n";
// }
