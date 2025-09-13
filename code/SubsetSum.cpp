/*
  Subset Sum (0/1)
  - can_sum(v, target): returns true if some subset sums to target
  - Optional reconstruction is easy by tracking choices; here we return bool only.
*/

#include <bits/stdc++.h>
using namespace std;

bool can_sum(const vector<int>& v, int target) {
  vector<char> dp(target + 1, 0);
  dp[0] = 1;
  for (int a : v) {
    for (int s = target; s >= a; --s) dp[s] = dp[s] || dp[s - a];
  }
  return dp[target];
}

// Example usage:
// int main(){
//   vector<int> v = {3, 34, 4, 12, 5, 2};
//   cout << can_sum(v, 9) << "\n"; // 1
// }

