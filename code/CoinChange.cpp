/*
  Coin Change problems
  - ways_unbounded(amount, coins): number of ways to make amount with unlimited coins (order-insensitive)
  - min_coins_unbounded(amount, coins): minimum number of coins to make amount (INF if impossible)
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF64 = (1LL<<60);

long long ways_unbounded(int amount, const vector<int>& coins) {
  vector<long long> dp(amount + 1, 0);
  dp[0] = 1;
  for (int c : coins) {
    for (int x = c; x <= amount; ++x) dp[x] += dp[x - c];
  }
  return dp[amount];
}

long long min_coins_unbounded(int amount, const vector<int>& coins) {
  vector<long long> dp(amount + 1, INF64);
  dp[0] = 0;
  for (int x = 1; x <= amount; ++x) {
    for (int c : coins) if (c <= x) dp[x] = min(dp[x], dp[x - c] + 1);
  }
  return dp[amount] >= INF64 ? -1 : dp[amount];
}

// Example usage:
// int main(){
//   vector<int> coins = {1, 2, 5};
//   cout << ways_unbounded(10, coins) << "\n"; // 10
//   cout << min_coins_unbounded(11, coins) << "\n"; // 3 (5+5+1)
// }

