/*
  Intersection of two convex polygons in O(n+m)
  - Polygons A, B in CCW order, no repeats
  - Returns convex polygon (possibly empty)
*/

#include <bits/stdc++.h>
using namespace std;

struct P { double x,y; };
double cross(P a, P b, P c){ return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); }
bool inside(P a, P b, P p){ return cross(a,b,p) >= -1e-12; }
P line_inter(P a, P b, P c, P d){ double A=cross(a,b,c), B=cross(a,b,d); P r; r.x = (d.x*A - c.x*B)/(A-B); r.y = (d.y*A - c.y*B)/(A-B); return r; }

vector<P> convex_intersect(vector<P> A, vector<P> B){
  vector<P> res=A;
  int m=B.size();
  for(int i=0;i<m;++i){ P a=B[i], b=B[(i+1)%m]; vector<P> cur; if(res.empty()) return {};
    for(int j=0;j<(int)res.size();++j){ P p=res[j], q=res[(j+1)%res.size()]; bool pin=inside(a,b,p), qin=inside(a,b,q);
      if(pin && qin) cur.push_back(q);
      else if(pin && !qin){ cur.push_back(line_inter(a,b,p,q)); }
      else if(!pin && qin){ cur.push_back(line_inter(a,b,p,q)); cur.push_back(q); }
    }
    res.swap(cur);
  }
  return res;
}

