/*
  Sparse Table for idempotent, associative operations (e.g., min, max, gcd)
  - Build O(n log n), query O(1)
*/

#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
  int n, K; vector<int> lg; vector<vector<long long>> st;
  function<long long(long long,long long)> f;
  SparseTable() {}
  SparseTable(const vector<long long>& a, function<long long(long long,long long)> op) { build(a, op); }
  void build(const vector<long long>& a, function<long long(long long,long long)> op) {
    f = op; n = (int)a.size(); K = 32 - __builtin_clz(n);
    lg.assign(n + 1, 0); for (int i = 2; i <= n; ++i) lg[i] = lg[i/2] + 1;
    st.assign(K, vector<long long>(n)); st[0].assign(a.begin(), a.end());
    for (int k = 1; k < K; ++k) {
      int len = 1 << k;
      for (int i = 0; i + len <= n; ++i) st[k][i] = f(st[k-1][i], st[k-1][i + (len>>1)]);
    }
  }
  long long query(int l, int r) const { // [l, r)
    int k = lg[r - l];
    return f(st[k][l], st[k][r - (1 << k)]);
  }
};

