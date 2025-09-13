/*
  Segment tree with lazy propagation
  Operation: range flip (0 <-> 1) and range sum query
  - update(l, r): flip bits in [l, r) (half-open)
  - query(l, r): sum of ones in [l, r)

  Notes:
  - All operations are O(log N)
  - Uses lazy XOR flag; flipping a segment of length L: sum = L - sum
*/

#include <bits/stdc++.h>
using namespace std;

struct SegTreeFlip {
  int n;                 // array size
  vector<int> seg;       // sums
  vector<unsigned char> lazy; // lazy flip flags (0/1)

  SegTreeFlip(int n = 0) { init(n); }

  void init(int n_) {
    n = n_;
    seg.assign(4 * max(1, n), 0);
    lazy.assign(4 * max(1, n), 0);
  }

  // apply flip to node covering [l, r)
  inline void apply(int id, int l, int r) {
    seg[id] = (r - l) - seg[id];
    lazy[id] ^= 1;
  }

  inline void push(int id, int l, int r) {
    if (!lazy[id] || r - l == 1) return;
    int m = (l + r) >> 1;
    int lc = id << 1, rc = lc | 1;
    apply(lc, l, m);
    apply(rc, m, r);
    lazy[id] = 0;
  }

  // build from initial array a (0/1 values)
  void build(const vector<int>& a, int id, int l, int r) {
    if (r - l == 1) { seg[id] = (l < (int)a.size() ? a[l] : 0); return; }
    int m = (l + r) >> 1, lc = id << 1, rc = lc | 1;
    build(a, lc, l, m);
    build(a, rc, m, r);
    seg[id] = seg[lc] + seg[rc];
  }
  void build(const vector<int>& a) { init((int)a.size()); build(a, 1, 0, n); }

  // flip [ql, qr)
  void update(int ql, int qr, int id, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) { apply(id, l, r); return; }
    push(id, l, r);
    int m = (l + r) >> 1, lc = id << 1, rc = lc | 1;
    update(ql, qr, lc, l, m);
    update(ql, qr, rc, m, r);
    seg[id] = seg[lc] + seg[rc];
  }
  void update(int l, int r) { update(l, r, 1, 0, n); }

  // sum [ql, qr)
  int query(int ql, int qr, int id, int l, int r) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return seg[id];
    push(id, l, r);
    int m = (l + r) >> 1;
    return query(ql, qr, id << 1, l, m) + query(ql, qr, id << 1 | 1, m, r);
  }
  int query(int l, int r) { return query(l, r, 1, 0, n); }
};

// Example usage:
// int main(){
//   vector<int> a = {0,1,0,1,1,0};
//   SegTreeFlip st; st.build(a);
//   cout << st.query(0, 6) << "\n"; // 3
//   st.update(1, 5); // flip indices [1..4]
//   cout << st.query(0, 6) << "\n"; // updated sum
// }

