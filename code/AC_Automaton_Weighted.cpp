/*
  Aho-Corasick with weights/counts
  - add(pattern, weight), build(), match(text): total weight of matches and per pattern counts
*/

#include <bits/stdc++.h>
using namespace std;

struct ACWeighted {
  struct Node { int next[26]; int link=-1; long long out=0; vector<int> ids; Node(){ memset(next,-1,sizeof(next)); } };
  vector<Node> t; vector<long long> w; ACWeighted(){ t.push_back(Node()); }
  int add(const string& s, long long weight){ int v=0; for(char cc: s){ int c=cc-'a'; if(t[v].next[c]==-1){ t[v].next[c]=t.size(); t.push_back(Node()); } v=t[v].next[c]; } t[v].ids.push_back(w.size()); w.push_back(weight); return (int)w.size()-1; }
  void build(){ queue<int> q; t[0].link=0; for(int c=0;c<26;++c){ int u=t[0].next[c]; if(u==-1) t[0].next[c]=0; else { t[u].link=0; q.push(u); } }
    while(!q.empty()){ int v=q.front(); q.pop(); t[v].out += t[t[v].link].out; for(int id: t[v].ids) t[v].out += w[id]; for(int c=0;c<26;++c){ int u=t[v].next[c]; if(u==-1) t[v].next[c]=t[t[v].link].next[c]; else { t[u].link = t[t[v].link].next[c]; q.push(u); } } }
  }
  long long match_total(const string& s){ int v=0; long long sum=0; for(char cc: s){ int c=cc-'a'; v=t[v].next[c]; sum += t[v].out; } return sum; }
};

