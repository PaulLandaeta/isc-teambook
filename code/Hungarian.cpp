/*
  Hungarian algorithm (assignment problem, min-cost perfect matching on bipartite graph)
  Complexity: O(n^2 m) for n x m cost matrix; O(n^3) for square matrix.

  Interface:
    - Hungarian hung(n, m);            // n rows (left), m cols (right)
    - hung.addCost(i, j, cost);        // 0 <= i < n, 0 <= j < m
    - auto [minCost, matchR] = hung.solve();
        * minCost: minimal total cost (long long)
        * matchR: size m, matchR[j] = i matched to column j, or -1

  Notes:
    - If m < n, pad with dummy columns of zero cost or swap sides.
    - This implementation works for any rectangular matrix.
*/

#include <bits/stdc++.h>
using namespace std;

struct Hungarian {
  int n, m;                         // rows (left), cols (right)
  const long long INF = (1LL<<62);
  vector<vector<long long>> a;      // costs

  Hungarian(int n, int m) : n(n), m(m), a(n, vector<long long>(m, 0)) {}
  void addCost(int i, int j, long long c) { a[i][j] = c; }

  pair<long long, vector<int>> solve() {
    // Implementation with potentials (u, v) and matching p/way (cols indexed 1..m)
    // Converts to 1-indexed per classic formulation
    int n1 = n, m1 = m;
    int N = max(n1, m1);
    vector<long long> u(N + 1, 0), v(N + 1, 0);
    vector<int> p(N + 1, 0), way(N + 1, 0);

    // Build square matrix by padding with zeros if needed
    vector<vector<long long>> cost(N + 1, vector<long long>(N + 1, 0));
    for (int i = 1; i <= n1; ++i)
      for (int j = 1; j <= m1; ++j)
        cost[i][j] = a[i-1][j-1];

    for (int i = 1; i <= N; ++i) {
      p[0] = i; int j0 = 0; vector<long long> minv(N + 1, INF); vector<char> used(N + 1, false);
      do {
        used[j0] = true; int i0 = p[j0]; long long delta = INF; int j1 = 0;
        for (int j = 1; j <= N; ++j) if (!used[j]) {
          long long cur = cost[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
          if (minv[j] < delta) { delta = minv[j]; j1 = j; }
        }
        for (int j = 0; j <= N; ++j) {
          if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
          else minv[j] -= delta;
        }
        j0 = j1;
      } while (p[j0] != 0);
      do { int j1 = way[j0]; p[j0] = p[j1]; j0 = j1; } while (j0);
    }

    vector<int> matchR(m, -1); // column j matched to row i
    vector<int> matchL(n, -1);
    for (int j = 1; j <= N; ++j) if (p[j] != 0) {
      int i = p[j];
      if (j <= m && i <= n) { matchR[j-1] = i-1; matchL[i-1] = j-1; }
    }
    long long minCost = 0;
    for (int j = 0; j < m; ++j) if (matchR[j] != -1) minCost += a[matchR[j]][j];
    return {minCost, matchR};
  }
};

// Example usage:
// int main() {
//   int n = 3, m = 3; Hungarian H(n, m);
//   long long C[3][3] = {{4,1,3},{2,0,5},{3,2,2}};
//   for (int i=0;i<n;++i) for (int j=0;j<m;++j) H.addCost(i,j,C[i][j]);
//   auto [cost, matchR] = H.solve();
//   cout << cost << "\n"; // expected 5
//   // matchR[j] = i
// }

