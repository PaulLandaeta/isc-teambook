/*
  Manacher's algorithm - longest palindromic substring in O(n)
  - manacher_odd(s): d1[i] = radius of odd-length palindrome centered at i
  - manacher_even(s): d2[i] = radius of even-length palindrome centered between i-1 and i
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(const string& s) {
  int n = (int)s.size();
  vector<int> d1(n);
  int l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = 1;
    if (i <= r) k = min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) ++k;
    d1[i] = k;
    if (i + k - 1 > r) { l = i - k + 1; r = i + k - 1; }
  }
  return d1;
}

vector<int> manacher_even(const string& s) {
  int n = (int)s.size();
  vector<int> d2(n);
  int l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = 0;
    if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
    d2[i] = k;
    if (i + k - 1 > r) { l = i - k; r = i + k - 1; }
  }
  return d2;
}
