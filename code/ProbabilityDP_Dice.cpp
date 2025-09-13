/*
  Probability DP: Dice sums
  - dice_sum_pmf(n, faces): returns vector p where p[s] = P(sum == s) for n fair dice with 'faces' faces (values 1..faces)
  - prob_sum_at_least(n, faces, thr): returns P(sum >= thr)
  Complexity: O(n * faces * max_sum)
*/

#include <bits/stdc++.h>
using namespace std;

vector<double> dice_sum_pmf(int n, int faces = 6) {
  if (n <= 0) return {1.0};
  int minS = n, maxS = n * faces;
  vector<double> dp_prev(maxS + 1, 0.0), dp_cur(maxS + 1, 0.0);
  // one die
  for (int d = 1; d <= faces; ++d) dp_prev[d] = 1.0 / faces;
  for (int k = 2; k <= n; ++k) {
    fill(dp_cur.begin(), dp_cur.end(), 0.0);
    for (int s = (k - 1); s <= (k - 1) * faces; ++s) if (dp_prev[s] > 0) {
      for (int d = 1; d <= faces; ++d) dp_cur[s + d] += dp_prev[s] / faces;
    }
    dp_prev.swap(dp_cur);
  }
  return vector<double>(dp_prev.begin(), dp_prev.end());
}

double prob_sum_at_least(int n, int faces, int thr) {
  auto p = dice_sum_pmf(n, faces);
  int maxS = n * faces;
  thr = max(thr, 0);
  if (thr > maxS) return 0.0;
  double ans = 0.0;
  for (int s = thr; s < (int)p.size(); ++s) ans += p[s];
  return ans;
}

// Example usage:
// int main(){
//   cout.setf(std::ios::fixed); cout<<setprecision(6);
//   cout << prob_sum_at_least(3, 6, 10) << "\n";
// }

