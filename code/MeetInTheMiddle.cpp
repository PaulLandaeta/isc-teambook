/*
  Meet-in-the-Middle (MITM) templates
  - subset_sums(v): all subset sums of vector v (size up to ~30 OK)
  - max_subset_sum_leq(v, W): maximum subset sum <= W
  - count_target_sum(v, S): number of subsets with sum exactly S
  Notes:
    For max_subset_sum_leq, sorts one side and binary searches best complement.
*/

#include <bits/stdc++.h>
using namespace std;

vector<long long> subset_sums(const vector<long long>& a) {
  int n = (int)a.size();
  vector<long long> sums; sums.reserve(1 << min(n, 20));
  for (int m = 0; m < (1 << n); ++m) {
    long long s = 0;
    for (int i = 0; i < n; ++i) if (m & (1 << i)) s += a[i];
    sums.push_back(s);
  }
  return sums;
}

long long max_subset_sum_leq(const vector<long long>& v, long long W) {
  int n = (int)v.size();
  int nL = n / 2; int nR = n - nL;
  vector<long long> L(v.begin(), v.begin() + nL), R(v.begin() + nL, v.end());
  auto sL = subset_sums(L), sR = subset_sums(R);
  sort(sR.begin(), sR.end());
  long long best = LLONG_MIN;
  for (long long x : sL) {
    if (x > W) continue;
    long long rem = W - x;
    auto it = upper_bound(sR.begin(), sR.end(), rem);
    if (it != sR.begin()) {
      --it;
      best = max(best, x + *it);
    } else {
      best = max(best, x); // possibly 0 if empty subset
    }
  }
  return (best == LLONG_MIN ? LLONG_MIN : best);
}

long long count_target_sum(const vector<long long>& v, long long S) {
  int n = (int)v.size();
  int nL = n / 2; int nR = n - nL;
  vector<long long> L(v.begin(), v.begin() + nL), R(v.begin() + nL, v.end());
  auto sL = subset_sums(L), sR = subset_sums(R);
  sort(sR.begin(), sR.end());
  long long cnt = 0;
  for (long long x : sL) {
    long long need = S - x;
    auto range = equal_range(sR.begin(), sR.end(), need);
    cnt += (range.second - range.first);
  }
  return cnt;
}

// Example usage:
// int main(){
//   vector<long long> v = {3, 34, 4, 12, 5, 2};
//   cout << max_subset_sum_leq(v, 10) << "\n"; // e.g., 10
//   cout << count_target_sum(v, 9) << "\n";     // subsets that sum to 9
// }

