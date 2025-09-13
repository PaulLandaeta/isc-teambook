/*
  Minkowski Sum of two convex polygons in O(n+m)
  - Polygons A, B in CCW order and without duplicates
*/

#include <bits/stdc++.h>
using namespace std;

struct V { long long x,y; };
V operator+(V a,V b){ return {a.x+b.x, a.y+b.y}; }
V operator-(V a,V b){ return {a.x-b.x, a.y-b.y}; }
long long cross(V a,V b){ return a.x*b.y - a.y*b.x; }

int lowest_left(const vector<V>& P){ int n=P.size(), idx=0; for(int i=1;i<n;++i) if(P[i].y<P[idx].y || (P[i].y==P[idx].y && P[i].x<P[idx].x)) idx=i; return idx; }

vector<V> minkowski_sum(vector<V> A, vector<V> B){
  int n=A.size(), m=B.size(); if(n==0||m==0) return {};
  int ia=lowest_left(A), ib=lowest_left(B); rotate(A.begin(), A.begin()+ia, A.end()); rotate(B.begin(), B.begin()+ib, B.end()); A.push_back(A[0]); B.push_back(B[0]);
  vector<V> edgeA, edgeB; for(int i=0;i<n;++i) edgeA.push_back(A[i+1]-A[i]); for(int i=0;i<m;++i) edgeB.push_back(B[i+1]-B[i]);
  vector<V> C; C.reserve(n+m); V cur = {A[0].x+B[0].x, A[0].y+B[0].y}; C.push_back(cur);
  int i=0,j=0; while(i<n || j<m){ if(j==m || (i<n && cross(edgeA[i], edgeB[j]) >= 0)) cur = cur + edgeA[i++]; else cur = cur + edgeB[j++]; C.push_back(cur); }
  C.pop_back(); return C;
}

