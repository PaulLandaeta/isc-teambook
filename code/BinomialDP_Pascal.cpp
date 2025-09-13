/*
  Binomial coefficients via Pascal's triangle
  - pascal_binom(N): C[n][k] for 0<=n<=N without modulus (watch overflow)
  - pascal_binom_mod(N, MOD): C[n][k] mod MOD (works for any MOD)
*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<unsigned long long>> pascal_binom(int N){
  vector<vector<unsigned long long>> C(N+1, vector<unsigned long long>(N+1, 0));
  for (int n=0;n<=N;++n){ C[n][0]=C[n][n]=1ULL; for (int k=1;k<n;++k) C[n][k]=C[n-1][k-1]+C[n-1][k]; }
  return C;
}

vector<vector<long long>> pascal_binom_mod(int N, long long MOD){
  vector<vector<long long>> C(N+1, vector<long long>(N+1, 0));
  for (int n=0;n<=N;++n){ C[n][0]=C[n][n]=1%MOD; for (int k=1;k<n;++k){ C[n][k]= (C[n-1][k-1]+C[n-1][k])%MOD; } }
  return C;
}

// Example usage:
// int main(){ auto C = pascal_binom_mod(5, 1000000007LL); cout << C[5][2] << "\n"; }

