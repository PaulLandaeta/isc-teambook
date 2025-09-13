/*
  Link-Cut Tree (Splay-based) - dynamic trees
  Supports:
    - make_root(x), link(u,v), cut(u,v), connected(u,v)
    - path aggregate (sum) via access(u), access(v), makeroot(u), then expose
  Notes:
    - This template keeps a value per node and maintains path-sum as example.
*/

#include <bits/stdc++.h>
using namespace std;

struct LCT {
  struct Node {
    int ch[2] = {-1,-1}, p = -1;
    bool rev = false;
    long long val = 0, sum = 0; // path aggregate
  };
  vector<Node> t;
  LCT(int n=0){init(n);} void init(int n){ t.assign(n, Node()); }
  bool is_root(int x){ int p=t[x].p; return p==-1 || (t[p].ch[0]!=x && t[p].ch[1]!=x); }
  void push(int x){ if(!x){} if(t[x].rev){ int &l=t[x].ch[0], &r=t[x].ch[1]; swap(l,r); if(l!=-1) t[l].rev^=1; if(r!=-1) t[r].rev^=1; t[x].rev=false; } }
  void pull(int x){ t[x].sum = t[x].val; for(int d=0; d<2; ++d){ int c=t[x].ch[d]; if(c!=-1) t[x].sum += t[c].sum; } }
  void rot(int x){ int p=t[x].p, g=t[p].p; push(p); push(x); int dir=(t[p].ch[1]==x); int b=t[x].ch[dir^1]; if(!is_root(p)){ if(t[g].ch[0]==p) t[g].ch[0]=x; else if(t[g].ch[1]==p) t[g].ch[1]=x; } t[x].p=g; t[x].ch[dir^1]=p; t[p].p=x; t[p].ch[dir]=b; if(b!=-1) t[b].p=p; pull(p); pull(x); }
  void splay(int x){ static vector<int> st; st.clear(); int y=x; st.push_back(y); while(!is_root(y)){ y=t[y].p; st.push_back(y);} while(!st.empty()){ push(st.back()); st.pop_back(); }
    while(!is_root(x)){ int p=t[x].p, g=t[p].p; if(!is_root(p)) ((t[p].ch[0]==x)^(t[g].ch[0]==p))? rot(x):rot(p); rot(x); } }
  int access(int x){ int last=-1; for(int y=x; y!=-1; y=t[y].p){ splay(y); t[y].ch[1]=last; pull(y); last=y; } splay(x); return last; }
  void make_root(int x){ access(x); t[x].rev^=1; push(x); }
  int find_root(int x){ access(x); while(t[x].ch[0]!=-1){ push(x); x=t[x].ch[0]; } splay(x); return x; }
  bool connected(int u,int v){ if(u==v) return true; access(u); int r=access(v); return r!=-1; }
  bool link(int u,int v){ make_root(u); if(find_root(v)==u) return false; t[u].p=v; return true; }
  bool cut(int u,int v){ make_root(u); access(v); // now u is root, path u-v on preferred path, v on top
    if(t[v].ch[0]!=-1){ int w=t[v].ch[0];
      push(v); while(t[w].ch[1]!=-1){ push(w); w=t[w].ch[1]; }
    }
    if(t[v].ch[0]==u && t[u].ch[1]==-1){ t[v].ch[0]=-1; t[u].p=-1; pull(v); return true; }
    return false; }
  // Path sum query: sum on path u-v
  long long path_sum(int u,int v){ make_root(u); access(v); return t[v].sum; }
  // Set value at node x
  void set_val(int x,long long v){ access(x); t[x].val=v; pull(x); }
};

// Example usage:
// int main(){ LCT l(5); l.set_val(0,1); l.set_val(1,2); l.link(0,1); cout<<l.path_sum(0,1)<<"\n"; }
