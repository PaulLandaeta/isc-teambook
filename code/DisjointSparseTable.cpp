/*
  Disjoint Sparse Table (DST) - static RMQ/idempotent queries in O(1)
  - Build O(n log n), Query O(1) (assumes associative idempotent op like min/max/gcd)
*/

#include <bits/stdc++.h>
using namespace std;

struct DisjointSparseTable {
  using T = long long;
  function<T(const T&, const T&)> f; int n, K; vector<vector<T>> leftT, rightT; vector<int> lg;
  DisjointSparseTable(){}
  DisjointSparseTable(const vector<T>& a, function<T(const T&,const T&)> op){ build(a,op);} 
  void build(const vector<T>& a, function<T(const T&,const T&)> op){ f=op; n=a.size(); K=32-__builtin_clz(n); leftT.assign(K, vector<T>(n)); rightT.assign(K, vector<T>(n)); lg.assign(n+1,0); for(int i=2;i<=n;++i) lg[i]=lg[i/2]+1; 
    for(int k=0;k<K;++k){ int len=1<<k; for(int i=0;i<n; i+= (len<<1)){ int mid=min(i+len, n), r=min(i+(len<<1), n);
        leftT[k][mid-1]=a[mid-1]; for(int j=mid-2;j>=i;--j) leftT[k][j]=f(a[j], leftT[k][j+1]);
        if(mid<r){ rightT[k][mid]=a[mid]; for(int j=mid+1;j<r;++j) rightT[k][j]=f(rightT[k][j-1], a[j]); }
      }
    }
  }
  T query(int l,int r){ // inclusive l..r
    if(l==r) return leftT[0][l]; int k=lg[l^r]; return f(leftT[k][l], rightT[k][r]);
  }
};
