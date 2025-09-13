/*
  0/1 Knapsack
  - knap01(weights, values, W): maximum value with total weight <= W
  - Complexity: O(n * W)
*/

#include <bits/stdc++.h>
using namespace std;

long long knap01(const vector<int>& w, const vector<int>& v, int W) {
  int n = (int)w.size();
  vector<long long> dp(W + 1, 0);
  for (int i = 0; i < n; ++i) {
    for (int c = W; c >= w[i]; --c) dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
  }
  return dp[W];
}

// Example usage:
// int main(){
//   vector<int> w = {3,2,1}, v = {5,3,4}; int W = 5;
//   cout << knap01(w, v, W) << "\n"; // 9
// }

