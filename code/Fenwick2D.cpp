/*
  Fenwick Tree (Binary Indexed Tree) 2D
  - add(x,y,delta) and sum(x,y) for rectangle [1..x][1..y]
  - rectangle sum [x1..x2][y1..y2] via inclusion-exclusion
*/

#include <bits/stdc++.h>
using namespace std;

struct BIT2D {
  int n,m; vector<vector<long long>> bit;
  BIT2D(int n=0,int m=0){init(n,m);} void init(int n_,int m_){ n=n_; m=m_; bit.assign(n+1, vector<long long>(m+1,0)); }
  void add(int x,int y,long long v){ for(int i=x;i<=n;i+=i&-i) for(int j=y;j<=m;j+=j&-j) bit[i][j]+=v; }
  long long sum(int x,int y) const { long long r=0; for(int i=x;i>0;i-=i&-i) for(int j=y;j>0;j-=j&-j) r+=bit[i][j]; return r; }
  long long rect(int x1,int y1,int x2,int y2) const { // inclusive
    return sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1);
  }
};

