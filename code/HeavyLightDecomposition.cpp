/*
  Heavy-Light Decomposition (HLD) + Segment Tree (sum)
  - build from tree edges (0-based)
  - path_query(u,v), path_update(u,v,delta) as examples
*/

#include <bits/stdc++.h>
using namespace std;

struct SegTree {
  int n; vector<long long> st, lz;
  SegTree(int n=0){init(n);} void init(int n_){ n=1; while(n<n_) n<<=1; st.assign(2*n,0); lz.assign(2*n,0);} 
  void apply(int p,long long v,int len){ st[p]+=v*len; lz[p]+=v; }
  void push(int p,int len){ if(lz[p]){ apply(p<<1,lz[p],len>>1); apply(p<<1|1,lz[p],len>>1); lz[p]=0; }}
  void upd(int l,int r,long long v,int p,int s,int e){ if(r<=s||e<=l) return; if(l<=s&&e<=r){ apply(p,v,e-s); return;} push(p,e-s); int m=(s+e)>>1; upd(l,r,v,p<<1,s,m); upd(l,r,v,p<<1|1,m,e); st[p]=st[p<<1]+st[p<<1|1]; }
  long long qry(int l,int r,int p,int s,int e){ if(r<=s||e<=l) return 0; if(l<=s&&e<=r) return st[p]; push(p,e-s); int m=(s+e)>>1; return qry(l,r,p<<1,s,m)+qry(l,r,p<<1|1,m,e); }
  void update(int l,int r,long long v){ upd(l,r,v,1,0,n); }
  long long query(int l,int r){ return qry(l,r,1,0,n);} // [l,r)
};

struct HLD {
  int n; vector<vector<int>> g; vector<int> par, depth, heavy, head, pos, sz; int cur;
  SegTree st;
  HLD(int n=0){init(n);} void init(int n_){ n=n_; g.assign(n,{}); par.assign(n,-1); depth.assign(n,0); heavy.assign(n,-1); head.assign(n,0); pos.assign(n,0); sz.assign(n,0); cur=0; }
  void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }
  int dfs(int v,int p){ par[v]=p; sz[v]=1; int mx=0; for(int to:g[v]) if(to!=p){ depth[to]=depth[v]+1; int s=dfs(to,v); sz[v]+=s; if(s>mx){ mx=s; heavy[v]=to; } } return sz[v]; }
  void decompose(int v,int h){ head[v]=h; pos[v]=cur++; if(heavy[v]!=-1) decompose(heavy[v],h); for(int to:g[v]) if(to!=par[v] && to!=heavy[v]) decompose(to,to); }
  void build(int root=0){ dfs(root,-1); decompose(root,root); st.init(n); }
  // path update/query on [u,v]
  void path_update(int u,int v,long long val){ while(head[u]!=head[v]){ if(depth[head[u]]<depth[head[v]]) swap(u,v); st.update(pos[head[u]], pos[u]+1, val); u=par[head[u]]; } if(depth[u]>depth[v]) swap(u,v); st.update(pos[u], pos[v]+1, val); }
  long long path_query(int u,int v){ long long res=0; while(head[u]!=head[v]){ if(depth[head[u]]<depth[head[v]]) swap(u,v); res += st.query(pos[head[u]], pos[u]+1); u=par[head[u]]; } if(depth[u]>depth[v]) swap(u,v); res += st.query(pos[u], pos[v]+1); return res; }
};

// Example usage:
// int main(){ HLD h(5); h.addEdge(0,1); h.addEdge(1,2); h.addEdge(1,3); h.addEdge(3,4); h.build(0); h.path_update(2,4,1); cout<<h.path_query(0,4)<<"\n"; }

