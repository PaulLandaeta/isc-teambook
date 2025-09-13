/*
  DSU on Tree (Sack) - process subtree queries efficiently
  Template counts frequency-based answers using keep/big-child trick.
  Example provided: for each node, number of colors with max frequency in its subtree.
*/

#include <bits/stdc++.h>
using namespace std;

struct DSUOnTree {
  int n; vector<vector<int>> g; vector<int> col, sz, big; vector<long long> ans;
  unordered_map<int,int> cnt; int maxf=0; long long sumColors=0; // example state
  DSUOnTree(int n, const vector<vector<int>>& g, const vector<int>& color)
    : n(n), g(g), col(color), sz(n,0), big(n,0), ans(n,0) {}
  int dfs_sz(int v,int p){ sz[v]=1; int mx=0; for(int u:g[v]) if(u!=p){ int s=dfs_sz(u,v); sz[v]+=s; if(s>mx){mx=s; big[v]=u;} } return sz[v]; }
  void add_subtree(int v,int p,int add){ int c=col[v]; int &f=cnt[c]; if(add){ f++; if(f>maxf){ maxf=f; sumColors=c; } else if(f==maxf){ sumColors += c; } } else { // removal path not used in standard DSU-on-tree answer maintain
      f--; // left for completeness
  }
    for(int u:g[v]) if(u!=p && u!=skip) add_subtree(u,v,add);
  }
  int skip=-1;
  void dfs(int v,int p,bool keep){ for(int u:g[v]) if(u!=p && u!=big[v]) dfs(u,v,false); if(big[v]!=0) dfs(big[v],v,true), skip=big[v]; add_subtree(v,p,1); skip=-1; ans[v]=sumColors; if(!keep){ add_subtree(v,p,0); cnt.clear(); maxf=0; sumColors=0; } }
  vector<long long> solve(int root=0){ dfs_sz(root,-1); dfs(root,-1,true); return ans; }
};
