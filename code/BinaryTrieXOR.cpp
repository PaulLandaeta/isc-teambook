/*
  Binary Trie for XOR queries (0..31 bits)
  - insert(x), erase(x), max_xor(x), min_xor(x)
  - min_xor_pair(v): returns minimal xor of any pair (uses sorting trick)
*/

#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
  struct Node { int cnt=0; int nxt[2]={-1,-1}; };
  vector<Node> t; int B;
  BinaryTrie(int B=31){ this->B=B; t.assign(1, Node()); }
  void clear(){ t.assign(1, Node()); }
  void insert(unsigned int x){ int u=0; t[u].cnt++; for(int b=B;b>=0;--b){ int bit=(x>>b)&1; if(t[u].nxt[bit]==-1){ t[u].nxt[bit]=t.size(); t.push_back(Node()); } u=t[u].nxt[bit]; t[u].cnt++; } }
  void erase(unsigned int x){ int u=0; t[u].cnt--; for(int b=B;b>=0;--b){ int bit=(x>>b)&1; int v=t[u].nxt[bit]; u=v; t[u].cnt--; } }
  unsigned int max_xor(unsigned int x){ int u=0; unsigned int res=0; for(int b=B;b>=0;--b){ int bit=(x>>b)&1; int want=bit^1; int v=t[u].nxt[want]; if(v!=-1 && t[v].cnt>0){ res|=(1u<<b); u=v; } else u=t[u].nxt[bit]; } return res; }
  unsigned int min_xor(unsigned int x){ int u=0; unsigned int res=0; for(int b=B;b>=0;--b){ int bit=(x>>b)&1; int v=t[u].nxt[bit]; if(v!=-1 && t[v].cnt>0){ u=v; } else { res|=(1u<<b); u=t[u].nxt[bit^1]; } } return res; }
};

unsigned int min_xor_pair(vector<unsigned int> v){ sort(v.begin(), v.end()); unsigned int best = UINT_MAX; for(size_t i=1;i<v.size();++i) best=min(best, v[i]^v[i-1]); return best; }

