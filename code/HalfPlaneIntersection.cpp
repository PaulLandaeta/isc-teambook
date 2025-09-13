/*
  Half-Plane Intersection (HPI)
  - Intersects a set of half-planes (a,b,c) meaning ax+by<=c
  - Returns convex polygon (possibly empty) in CCW order
*/

#include <bits/stdc++.h>
using namespace std;

struct HP { double a,b,c, ang; }; // ax+by<=c
struct P { double x,y; };
double cross(double ax,double ay,double bx,double by){ return ax*by - ay*bx; }
P inter(const HP& u, const HP& v){ double det = cross(u.a,u.b,v.a,v.b); P p; p.x = (u.c*v.b - u.b*v.c)/det; p.y = (u.a*v.c - u.c*v.a)/det; return p; }
bool outside(const HP& h, const P& p){ return h.a*p.x + h.b*p.y > h.c + 1e-12; }

vector<P> halfplane_intersection(vector<HP> h){
  for(auto &x:h) x.ang = atan2(x.b, x.a);
  sort(h.begin(), h.end(), [](const HP& u, const HP& v){ if (fabs(u.ang - v.ang) > 1e-12) return u.ang < v.ang; // same angle: keep the most restrictive
    return u.c*sqrt(v.a*v.a+v.b*v.b) < v.c*sqrt(u.a*u.a+u.b*u.b);
  });
  deque<HP> dq; deque<P> pts;
  for(const auto& hp: h){
    while(!pts.empty() && outside(hp, pts.back())){ dq.pop_back(); pts.pop_back(); }
    if(!dq.empty() && fabs(cross(dq.back().a,dq.back().b,hp.a,hp.b)) < 1e-12){ // parallel
      if(outside(hp, {0,0}) && !dq.empty()) dq.pop_back(); else continue;
    }
    while(!pts.empty() && outside(hp, pts.front())){ dq.pop_front(); pts.pop_front(); }
    if(!dq.empty()) pts.push_back(inter(dq.back(), hp));
    dq.push_back(hp);
  }
  while(pts.size() && outside(dq.front(), pts.back())){ dq.pop_back(); pts.pop_back(); }
  if(dq.size() < 3) return {};
  pts.push_back(inter(dq.back(), dq.front()));
  return vector<P>(pts.begin(), pts.end());
}

