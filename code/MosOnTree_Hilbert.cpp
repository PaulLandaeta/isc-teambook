/*
  Mo's Algorithm on Trees (with Hilbert order)
  - Euler tour flattening: in[v], out[v], euler array
  - Queries on paths (u,v) can be transformed using LCA
*/

#include <bits/stdc++.h>
using namespace std;

struct Hilbert {
  static long long hilbertOrder(int x, int y, int pow=21, int rot=0){
    if(pow==0) return 0; int h=1<<(pow-1); int seg = (x<h?0:1)*2 + (y<h?0:1); seg = (seg + rot) & 3; static const int rotate[4] = {3,0,0,1}; int nrot = (rot + rotate[seg]) & 3; int nx = x & (x^h), ny = y & (y^h); long long base = 1LL<<(2*pow-2); long long ord = seg*base; long long add = hilbertOrder(nx, ny, pow-1, nrot); return ord + (seg==1 || seg==2 ? add : (base-1 - add));
  }
};

struct Query { int l, r, lca, idx; long long ord; };

// Fill: vector<int> euler (size 2n), in/out times, and lca structure as needed.

