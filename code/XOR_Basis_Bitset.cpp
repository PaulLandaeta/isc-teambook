/*
  XOR Linear Basis over GF(2) and bitset Gaussian elimination
  - insert(v): add vector v to basis, query max xor, etc.
*/

#include <bits/stdc++.h>
using namespace std;

struct XorBasis { // 0..63 bits
  static const int B=64; unsigned long long b[B]{}; bool insert(unsigned long long x){ for(int i=B-1;i>=0;--i){ if(!(x>>i&1)) continue; if(!b[i]){ b[i]=x; return true; } x^=b[i]; } return false; }
  unsigned long long get_max(unsigned long long x=0){ for(int i=B-1;i>=0;--i) x=max(x, x^b[i]); return x; }
};

// Bitset Gaussian elimination mod 2 for system A x = b
int gauss_bitset(vector< bitset<1024> >& A, vector<int>& where){ // augmented matrix, last column is b
  int n=A.size(), m=A[0].size()-1; where.assign(m,-1); int row=0;
  for(int col=0; col<m && row<n; ++col){ for(int i=row;i<n;++i) if(A[i][col]){ swap(A[i],A[row]); break; } if(!A[row][col]) continue; where[col]=row; for(int i=0;i<n;++i) if(i!=row && A[i][col]) A[i]^=A[row]; ++row; }
  // check consistency if needed
  return row; // rank
}

