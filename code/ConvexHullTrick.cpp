/*
  Convex Hull Trick (dynamic) for maximum query
  LineContainer (KACTL-style): add lines y = kx + m, query(x)
  Assumes queries are monotonic or not? This variant works in general using long double intersections.
*/

#include <bits/stdc++.h>
using namespace std;

struct Line {
  mutable long long k, m; mutable long double p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(long double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> { // max CHT
  static constexpr long double INF = std::numeric_limits<long double>::infinity();
  long double inter(const Line& a, const Line& b) const {
    if (a.k == b.k) return (a.m > b.m) ? -INF : INF;
    return (long double)(b.m - a.m) / (a.k - b.k);
  }
  bool isect(iterator x, iterator y){ if (y == end()) { x->p = INF; return false; } if (x->k == y->k) x->p = (x->m > y->m) ? -INF : INF; else x->p = inter(*x, *y); return x->p >= y->p; }
  void add(long long k, long long m){ auto z=insert({k,m,0}), y=z++, x=y; while(isect(y,z)) z=erase(z); if(x!=begin() && isect(--x,y)) isect(x, erase(y)); while((y=x) != begin() && (--x)->p >= y->p) isect(x, erase(y)); }
  long long query(long long x){ assert(!empty()); auto l = lower_bound((long double)x); return l->k * x + l->m; }
};
