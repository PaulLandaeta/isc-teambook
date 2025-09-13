/*
  Suffix Array + LCP (Kasai) - O(n log n) build, O(n) LCP
  - computeSA(): builds suffix array for string s (cyclic-safe variant as given)
  - computeLCP(): builds LCP array between adjacent suffixes in SA order

  This implementation mirrors a common contest template and includes:
    - macros for brevity (forn, forsn, etc.)
    - arrays r (SA order), p (rank), lcp (Kasai)

  Usage:
    s = "banana"; n = (int)s.size();
    computeSA();
    computeLCP();
*/

#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < (int)(n); i++)
#define forsn(i,s,n) for (int i = (int)(s); i < (int)(n); i++)
#define si(c) ((int)(c).size())

const int MAXN = 100000 + 100;

string s;
int n, t;
int r[MAXN], p[MAXN], lcp[MAXN], np_[MAXN];

inline bool bcomp(int i, int j) { return s[i] < s[j]; }
inline bool beq(int i, int j) { return s[i] == s[j]; }
inline bool comp(int i, int j) {
  return make_pair(p[i], p[(i + t) % n]) < make_pair(p[j], p[(j + t) % n]);
}
inline bool eq(int i, int j) {
  return make_pair(p[i], p[(i + t) % n]) == make_pair(p[j], p[(j + t) % n]);
}

void refine(bool (*eqf)(int,int)) {
  np_[r[0]] = 0;
  forsn(i, 1, n) {
    int ra = r[i], rp = r[i - 1];
    np_[ra] = np_[rp];
    if (!eqf(ra, rp)) np_[ra]++;
  }
  copy(np_, np_ + n, p);
}

void computeSA() {
  forn(i, n) r[i] = i;
  sort(r, r + n, bcomp);
  refine(beq);
  for (t = 1; t < 2 * n; t *= 2) {
    sort(r, r + n, comp);
    refine(eq);
  }
}

void computeLCP() {
  int L = 0;
  forn(i, n) if (p[i]) {
    int j = r[p[i] - 1];
    while (s[(i + L) % n] == s[(j + L) % n]) L++;
    lcp[p[i]] = L ? L-- : L;
  }
  lcp[0] = 0;
}

// Example (comment out in production):
// int main() {
//   s = "banana"; n = si(s);
//   computeSA();
//   computeLCP();
//   // r[k] is the k-th suffix index in sorted order
//   // p[i] is the rank of suffix starting at i
//   // lcp[k] = LCP between suffixes r[k-1] and r[k]
//   return 0;
// }
