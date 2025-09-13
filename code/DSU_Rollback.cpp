/*
  DSU with Rollback (no path compression)
  - unite(a,b) returns whether merged; can rollback() to previous state
  - Use in offline divide-and-conquer on time or segment tree over time
*/

#include <bits/stdc++.h>
using namespace std;

struct DSUrb {
  int n; vector<int> p, r; vector<pair<int,int>> st; int comps;
  DSUrb(int n=0){init(n);} void init(int n_){ n=n_; p.resize(n); r.assign(n,0); iota(p.begin(),p.end(),0); st.clear(); comps=n; }
  int find(int x){ while(x!=p[x]) x=p[x]; return x; }
  bool unite(int a,int b){ a=find(a); b=find(b); if(a==b){ st.emplace_back(-1,-1); return false; } if(r[a]<r[b]) swap(a,b); st.emplace_back(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; comps--; return true; }
  void rollback(){ auto [a,b]=st.back(); st.pop_back(); if(a==-1) return; p[b]=b; if(r[a]==r[b]+1) r[a]--; comps++; }
};

