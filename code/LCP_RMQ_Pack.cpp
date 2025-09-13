/*
  LCP RMQ pack for LCE queries
  - Build SA and LCP (refer to SuffixArrayLCP.cpp) then build Sparse Table over LCP
  - lce(i,j): longest common extension of suffixes i and j
*/

#include <bits/stdc++.h>
using namespace std;

struct LCPRMQ {
  vector<int> sa, rankv, lcp, lg; vector<vector<int>> st;
  void build(const string& s, const vector<int>& sa_, const vector<int>& lcp_){ sa=sa_; lcp=lcp_; int n=s.size(); rankv.assign(n,0); for(int i=0;i<n;++i) rankv[sa[i]]=i; int m=lcp.size(); lg.assign(m+1,0); for(int i=2;i<=m;++i) lg[i]=lg[i/2]+1; st.assign(lg[m]+1, vector<int>(m)); st[0]=lcp; for(int k=1;k<=lg[m];++k){ for(int i=0;i+(1<<k)<=m;++i) st[k][i]=min(st[k-1][i], st[k-1][i+(1<<(k-1))]); } }
  int rmq(int l,int r){ if(l>r) swap(l,r); // query on lcp between ranks (l+1..r)
    l++; if(l>r) return 0; int k=lg[r-l+1]; return min(st[k][l], st[k][r-(1<<k)+1]); }
  int lce(int i,int j){ if(i==j) return (int)sa.size()-i; int ri=rankv[i], rj=rankv[j]; return rmq(ri, rj); }
};

