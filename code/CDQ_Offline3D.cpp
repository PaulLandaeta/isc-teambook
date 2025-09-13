/*
  CDQ Divide & Conquer for 3D dominance counting
  - Points (x,y,z), count for each point how many points (<=x,<=y,<=z)
  - Template solves counting with coordinate compression
*/

#include <bits/stdc++.h>
using namespace std;

struct BIT1D { int n; vector<int> b; BIT1D(int n=0){init(n);} void init(int n_){ n=n_; b.assign(n+1,0);} void add(int i,int v){ for(;i<=n;i+=i&-i) b[i]+=v;} int sum(int i){ int r=0; for(;i>0;i-=i&-i) r+=b[i]; return r; } };

struct Point{ int x,y,z,idx,cnt; };

void cdq(vector<Point>& a, int l, int r, BIT1D& bit){ if(r-l<=1) return; int m=(l+r)>>1; cdq(a,l,m,bit); cdq(a,m,r,bit); vector<Point> L(a.begin()+l,a.begin()+m), R(a.begin()+m,a.begin()+r); sort(L.begin(),L.end(),[](auto &A,auto &B){return A.y<B.y;}); sort(R.begin(),R.end(),[](auto &A,auto &B){return A.y<B.y;}); int i=0; for(auto &p: R){ while(i<(int)L.size() && L[i].y<=p.y){ bit.add(L[i].z,1); ++i; } a[p.idx].cnt += bit.sum(p.z); } for(int j=0;j<i;++j) bit.add(L[j].z,-1); inplace_merge(a.begin()+l, a.begin()+m, a.begin()+r, [](auto &A,auto &B){ return A.y<B.y; }); }

// Example usage (compress coords, sort by x then y then z; then call cdq)

