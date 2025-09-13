/*
  Li Chao Tree (dynamic) for min query of lines y = m x + b
  - add_line(m, b)
  - query(x)
  Coordinates: x in [X_MIN, X_MAX]
*/

#include <bits/stdc++.h>
using namespace std;

struct LiChao {
  struct Line { long long m, b; long long get(long long x) const { return m*x + b; } };
  struct Node { Line ln; Node* l=nullptr; Node* r=nullptr; Node(Line ln):ln(ln){} };
  long long X_MIN, X_MAX; Node* root=nullptr; const long long INF = (1LL<<62);
  LiChao(long long xmin, long long xmax): X_MIN(xmin), X_MAX(xmax) {}
  void add_line(Line nw){ add_line(nw, X_MIN, X_MAX, root); }
  void add_line(long long m,long long b){ add_line({m,b}); }
  void add_segment(Line nw, long long L, long long R){ add_segment(nw, L, R, X_MIN, X_MAX, root); }
  long long query(long long x) const { return query(x, X_MIN, X_MAX, root); }
private:
  void add_line(Line nw, long long l, long long r, Node* &nd){ if(!nd){ nd=new Node(nw); return; } long long mid=(l+r)>>1; bool lef = nw.get(l) < nd->ln.get(l); bool mdd = nw.get(mid) < nd->ln.get(mid); if(mdd) swap(nw, nd->ln); if(r-l==1) return; if(lef!=mdd) add_line(nw, l, mid, nd->l); else add_line(nw, mid, r, nd->r); }
  void add_segment(Line nw, long long L, long long R, long long l, long long r, Node* &nd){ if(R<=l||r<=L) return; if(L<=l && r<=R){ add_line(nw, l, r, nd); return;} if(!nd) nd=new Node({0, INF}); long long mid=(l+r)>>1; add_segment(nw,L,R,l,mid,nd->l); add_segment(nw,L,R,mid,r,nd->r); }
  long long query(long long x, long long l, long long r, Node* nd) const { if(!nd) return INF; long long res = nd->ln.get(x); if(r-l==1) return res; long long mid=(l+r)>>1; if(x<mid) return min(res, query(x, l, mid, nd->l)); else return min(res, query(x, mid, r, nd->r)); }
};

