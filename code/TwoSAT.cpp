/*
  2-SAT using implication graph + SCC (Kosaraju)
  - n variables x in {0,1}. Index each literal as var*2 (false), var*2^1 (true)
  - add_imp(a, b): add implication a -> b (a,b are literal indices)
  - add_or(a, b): clause (a or b)
  - add_xor(a, b): (a xor b)
  - add_eq(a, b): a == b
  - solve(): returns {sat, assignment}
*/

#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
  int n; vector<vector<int>> g, gr; vector<int> comp, order, val;
  TwoSAT(int n=0){init(n);} void init(int n_){n=n_; g.assign(2*n,{}); gr.assign(2*n,{});} 
  static inline int var(int x, bool truth){ return x<<1 | (truth?1:0); }
  void add_imp(int a, int b){ g[a].push_back(b); gr[b].push_back(a);} 
  void add_or(int a, int b){ // (a or b) => (~a -> b) and (~b -> a)
    add_imp(a^1, b); add_imp(b^1, a);
  }
  void add_xor(int a, int b){ // (a xor b) => (a or b) and (~a or ~b)
    add_or(a, b); add_or(a^1, b^1);
  }
  void add_eq(int a, int b){ // a == b => (a->b) and (b->a) and (~a->~b) and (~b->~a)
    add_imp(a, b); add_imp(b, a); add_imp(a^1, b^1); add_imp(b^1, a^1);
  }
  pair<bool, vector<int>> solve(){
    int N=2*n; vector<char> used(N,0); order.clear(); comp.assign(N,-1);
    function<void(int)> dfs1=[&](int v){ used[v]=1; for(int to:g[v]) if(!used[to]) dfs1(to); order.push_back(v); };
    function<void(int,int)> dfs2=[&](int v,int c){ comp[v]=c; for(int to:gr[v]) if(comp[to]==-1) dfs2(to,c); };
    for(int i=0;i<N;++i) if(!used[i]) dfs1(i);
    int j=0; for(int i=N-1;i>=0;--i){ int v=order[i]; if(comp[v]==-1) dfs2(v,j++); }
    val.assign(n,0);
    for(int i=0;i<n;++i){ if(comp[2*i]==comp[2*i+1]) return {false,{}}; val[i]= comp[2*i] < comp[2*i+1]; }
    return {true, val};
  }
};

