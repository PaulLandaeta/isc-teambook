/*
  Markov Chains (small state) utilities
  - step_distribution(pi0, T, steps): apply transition matrix T 'steps' times to initial distribution pi0
  - stationary_distribution(T): power iteration to approximate stationary vector for an ergodic chain
  Assumes T is row-stochastic (rows sum to 1). Vectors are probabilities.
*/

#include <bits/stdc++.h>
using namespace std;

using Vec = vector<double>;
using Mat = vector<vector<double>>;

Vec mul(const Vec& v, const Mat& T) {
  int n = (int)T.size();
  Vec r(n, 0.0);
  for (int i = 0; i < n; ++i) if (v[i] != 0.0) {
    for (int j = 0; j < n; ++j) r[j] += v[i] * T[i][j];
  }
  return r;
}

Vec step_distribution(const Vec& pi0, const Mat& T, long long steps) {
  Vec pi = pi0; long long k = max(0LL, steps);
  while (k--) pi = mul(pi, T);
  return pi;
}

Vec stationary_distribution(const Mat& T, int iters = 10000, double tol = 1e-12) {
  int n = (int)T.size();
  Vec pi(n, 1.0 / n);
  for (int it = 0; it < iters; ++it) {
    Vec nxt = mul(pi, T);
    double diff = 0.0; for (int i = 0; i < n; ++i) diff = max(diff, fabs(nxt[i] - pi[i]));
    pi.swap(nxt);
    if (diff < tol) break;
  }
  return pi;
}

// Example usage:
// int main(){
//   Mat T = { {0.9, 0.1}, {0.5, 0.5} };
//   Vec pi0 = {1, 0};
//   auto pi = step_distribution(pi0, T, 10);
//   auto st = stationary_distribution(T);
//   cout.setf(std::ios::fixed); cout<<setprecision(6);
//   cout << pi[0] << " " << pi[1] << "\n";
//   cout << st[0] << " " << st[1] << "\n";
// }

