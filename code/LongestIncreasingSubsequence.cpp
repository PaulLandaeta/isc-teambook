/*
  Title: LongestIncreasingSubsequence
  Complexity: See algorithm notes in this file (typical bounds vary)
  Description: See functions below for details.
  Example:
  // int main(){
  //   // TODO: minimal example of using LongestIncreasingSubsequence
  //   return 0;
  // }
*/

// Longest Increasing Subsequence (LIS) with reconstruction
// - Time: O(n log n)
// - Provides strict and non-strict variants
//   * LongestIncreasingSubsequence(v): strictly increasing
//   * LongestIncreasingSubsequenceNonStrict(v): non-decreasing

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

VI LIS_impl(const VI& v, bool strict) {
  VPII best;               // stores pairs (value, index)
  VI dad(v.size(), -1);    // predecessor to reconstruct sequence

  for (int i = 0; i < (int)v.size(); i++) {
    PII key;
    if (strict) {
      // lower_bound on (value, -inf) for strictly increasing
      key = make_pair(v[i], INT_MIN);
      VPII::iterator it = lower_bound(best.begin(), best.end(), key);
      PII item = make_pair(v[i], i);
      if (it == best.end()) {
        dad[i] = best.empty() ? -1 : best.back().second;
        best.push_back(item);
      } else {
        dad[i] = (it == best.begin()) ? -1 : prev(it)->second;
        *it = item;
      }
    } else {
      // upper_bound on (value, +inf) for non-decreasing
      key = make_pair(v[i], INT_MAX);
      VPII::iterator it = upper_bound(best.begin(), best.end(), key);
      PII item = make_pair(v[i], i);
      if (it == best.end()) {
        dad[i] = best.empty() ? -1 : best.back().second;
        best.push_back(item);
      } else {
        dad[i] = (it == best.begin()) ? -1 : prev(it)->second;
        *it = item;
      }
    }
  }

  VI ret;
  if (best.empty()) return ret;
  for (int i = best.back().second; i >= 0; i = dad[i]) ret.push_back(v[i]);
  reverse(ret.begin(), ret.end());
  return ret;
}

VI LongestIncreasingSubsequence(VI v) {
  return LIS_impl(v, true);
}

VI LongestIncreasingSubsequenceNonStrict(VI v) {
  return LIS_impl(v, false);
}
