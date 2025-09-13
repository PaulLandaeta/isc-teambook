/*
  Mo's Algorithm (offline range queries on array)
  - Reorder queries to minimize add/remove cost; O((N+Q) * sqrt(N)) typical
  Template:
    - Define add(idx), remove(idx), and current answer structure
    - Fill queries {l,r,idx} (0-based, inclusive r)
    - Call solve to get answers vector in original order
*/

#include <bits/stdc++.h>
using namespace std;

struct Query { int l, r, idx; int block; };

// Example: count distinct values in range [l,r]
// Replace with your own add/remove logic
struct Mo {
  int n; const vector<int>& a; int B;
  vector<int> freq; int distinct = 0;
  Mo(const vector<int>& a): n((int)a.size()), a(a) {
    B = max(1, (int)(n / max(1.0, sqrt(n))));
    int maxv = 0; for (int x : a) maxv = max(maxv, x);
    freq.assign(max(1, maxv+1), 0);
  }
  void add(int i){ int x=a[i]; if (x>= (int)freq.size()) return; if (freq[x]++ == 0) ++distinct; }
  void remove_(int i){ int x=a[i]; if (x>= (int)freq.size()) return; if (--freq[x] == 0) --distinct; }
  vector<long long> solve(vector<Query> qs){
    for (auto& q : qs) q.block = q.l / B;
    sort(qs.begin(), qs.end(), [&](const Query& A, const Query& B){
      if (A.block != B.block) return A.block < B.block;
      if (A.block & 1) return A.r > B.r; // zig-zag to reduce movement
      return A.r < B.r;
    });
    vector<long long> ans(qs.size());
    int L=0, R=-1;
    for (auto &q : qs){
      while (L > q.l) add(--L);
      while (R < q.r) add(++R);
      while (L < q.l) remove_(L++);
      while (R > q.r) remove_(R--);
      ans[q.idx] = distinct;
    }
    return ans;
  }
};

// Example usage:
// int main(){
//   vector<int> a = {1,2,1,3,2,2,1};
//   vector<Query> qs = {{0,3,0,0},{2,5,1,0},{0,6,2,0}};
//   Mo mo(a); auto ans = mo.solve(qs);
//   for (auto x: ans) cout << x << "\n";
// }

