/*
  Kadane's Algorithm - Maximum Subarray Sum (O(n))
  - kadane(a): returns maximum subarray sum (works when all numbers are negative)
  - kadane_with_indices(a): returns {best_sum, [l, r]} for subarray a[l..r] inclusive
*/

#include <bits/stdc++.h>
using namespace std;

long long kadane(const vector<long long>& a) {
  long long best = LLONG_MIN, cur = 0;
  for (long long x : a) {
    cur = max(x, cur + x);
    best = max(best, cur);
  }
  return best;
}

pair<long long, pair<int,int>> kadane_with_indices(const vector<long long>& a) {
  long long best = LLONG_MIN, cur = 0;
  int bestL = 0, bestR = -1, curL = 0;
  for (int i = 0; i < (int)a.size(); ++i) {
    if (cur + a[i] < a[i]) { cur = a[i]; curL = i; }
    else { cur += a[i]; }
    if (cur > best) { best = cur; bestL = curL; bestR = i; }
  }
  return {best, {bestL, bestR}};
}

// Example usage:
// int main(){
//   vector<long long> a = {-2,1,-3,4,-1,2,1,-5,4};
//   auto res = kadane_with_indices(a);
//   cout << res.first << " [" << res.second.first << "," << res.second.second << "]\n"; // 6 [3,6]
// }
