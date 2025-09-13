/*
  DP Optimizations Cheat Sheet
  Divide & Conquer Optimization:
    dp[k][i] = min_{j< i} { dp[k-1][j] + C(j, i) }
    If argmin for i is non-decreasing (Knuth-Yao monotonicity), then we can do D&C on i with opt in a range.
    Recurrence: solve(l,r,optL,optR): mid=(l+r)/2, find best j in [optL,optR], recurse.

  Knuth Optimization:
    For quadrangle inequality and monotone opt, dp[i][j] = min_{i<=k<j} dp[i][k] + dp[k+1][j] + w(i,j)
    With quadrangle inequality and monotone opt(i,j) <= opt(i,j+1) <= opt(i+1,j+1), compute in O(n^2).

  Quadrangle Inequality:
    w(a,c) + w(b,d) <= w(a,d) + w(b,c) for a<=b<=c<=d.

  CHT / Li Chao for DP:
    When dp[i] = min_j (m_j * x_i + b_j), use Li Chao or Convex Hull Trick.
*/

#include <bits/stdc++.h>
using namespace std;

// Divide & Conquer Optimization template (1D)
template<class Cost>
void dnc_opt(int l, int r, int optL, int optR, const Cost& C, const vector<long long>& prev, vector<long long>& cur){
  if(l>r) return; int m=(l+r)>>1; pair<long long,int> best={LLONG_MAX, -1};
  for(int j=optL;j<=min(m,optR);++j){ long long cand = prev[j] + C(j,m); if(cand<best.first){ best={cand,j}; } }
  cur[m]=best.first; int opt=best.second; dnc_opt(l,m-1,optL,opt,C,prev,cur); dnc_opt(m+1,r,opt,optR,C,prev,cur);
}

