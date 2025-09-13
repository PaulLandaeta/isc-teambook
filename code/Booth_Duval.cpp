/*
  Booth's algorithm (minimum rotation) and Duval (Lyndon factorization)
*/

#include <bits/stdc++.h>
using namespace std;

int booth_min_rotation(const string& s){ string ss=s+s; int n=s.size(); int i=0, j=1, k=0; while(i<n && j<n && k<n){ char a=ss[i+k], b=ss[j+k]; if(a==b) ++k; else if(a>b){ i=i+k+1; if(i<=j) i=j+1; k=0; } else { j=j+k+1; if(j<=i) j=i+1; k=0; } } return min(i,j); }

vector<string> duval_lyndon(const string& s){ int n=s.size(); vector<string> fact; for(int i=0;i<n;){ int j=i+1, k=i; while(j<n && s[k]<=s[j]){ if(s[k]<s[j]) k=i; else k++; j++; } while(i<=k){ fact.push_back(s.substr(i, j-k)); i += j-k; } } return fact; }

