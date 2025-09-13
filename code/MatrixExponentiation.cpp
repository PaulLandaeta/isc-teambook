/*
  Matrix exponentiation (NxN) in O(N^3 log e)
  - mult(A,B,mod), power(A, e, mod)
*/

#include <bits/stdc++.h>
using namespace std;

using Mat = vector<vector<long long>>;

Mat mult(const Mat& A, const Mat& B, long long mod){
  int n=A.size(), m=B[0].size(), p=B.size();
  Mat C(n, vector<long long>(m,0));
  for(int i=0;i<n;++i)
    for(int k=0;k<p;++k) if(A[i][k]){
      long long aik=A[i][k]%mod;
      for(int j=0;j<m;++j) C[i][j]=(C[i][j]+aik*(B[k][j]%mod))%mod;
    }
  return C;
}

Mat power(Mat A, long long e, long long mod){
  int n=A.size(); Mat R(n, vector<long long>(n,0)); for(int i=0;i<n;++i) R[i][i]=1%mod;
  while(e){ if(e&1) R=mult(R,A,mod); A=mult(A,A,mod); e>>=1; }
  return R;
}

