/*
  Z-Function (linear time)
  - z[i] = length of longest substring starting at i which is also a prefix of s
  - z[0] = 0 by convention
  Applications: pattern matching on s = pattern#text, string properties
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
  int n = (int)s.size();
  vector<int> z(n, 0);
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
  }
  return z;
}

