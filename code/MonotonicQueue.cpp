/*
  Monotonic Queue for sliding window min/max in O(n)
  - window_min(a, k): minima of every subarray of length k
  - window_max(a, k): maxima of every subarray of length k
*/

#include <bits/stdc++.h>
using namespace std;

vector<long long> window_min(const vector<long long>& a, int k){
  deque<int> dq; vector<long long> res; int n=a.size();
  for(int i=0;i<n;++i){
    while(!dq.empty() && dq.front() <= i-k) dq.pop_front();
    while(!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
    dq.push_back(i);
    if(i>=k-1) res.push_back(a[dq.front()]);
  }
  return res;
}

vector<long long> window_max(const vector<long long>& a, int k){
  deque<int> dq; vector<long long> res; int n=a.size();
  for(int i=0;i<n;++i){
    while(!dq.empty() && dq.front() <= i-k) dq.pop_front();
    while(!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
    dq.push_back(i);
    if(i>=k-1) res.push_back(a[dq.front()]);
  }
  return res;
}

