/*
  Rotating Calipers: Diameter (farthest pair) of a convex polygon in O(n)
  - Assumes polygon is convex and given in CCW order without duplicates
  - Returns maximum squared distance and the pair indices
*/

#include <bits/stdc++.h>
using namespace std;

long long dist2(const pair<long long,long long>& a, const pair<long long,long long>& b){
  long long dx=a.first-b.first, dy=a.second-b.second; return dx*dx + dy*dy;
}

long long cross_ll(const pair<long long,long long>& a, const pair<long long,long long>& b, const pair<long long,long long>& c){
  long long x1=b.first-a.first, y1=b.second-a.second;
  long long x2=c.first-a.first, y2=c.second-a.second;
  return x1*y2 - x2*y1;
}

pair<long long, pair<int,int>> convex_diameter(const vector<pair<long long,long long>>& P){
  int n=P.size(); if(n==1) return {0,{0,0}}; if(n==2) return {dist2(P[0],P[1]),{0,1}};
  long long best=0; pair<int,int> bi={0,0};
  int j=1; for(int i=0;i<n;++i){ int ni=(i+1)%n; while(true){ int nj=(j+1)%n; long long cur = llabs(cross_ll(P[i], P[ni], P[nj])); long long prev = llabs(cross_ll(P[i], P[ni], P[j])); if(cur>prev) j=nj; else break; }
    long long d1=dist2(P[i], P[j]); if(d1>best){ best=d1; bi={i,j}; }
    long long d2=dist2(P[ni], P[j]); if(d2>best){ best=d2; bi={ni,j}; }
  }
  return {best, bi};
}

