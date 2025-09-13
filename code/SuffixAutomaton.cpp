/*
  Suffix Automaton (SAM)
  - add(char), longest common substring, count distinct substrings, occurrences
*/

#include <bits/stdc++.h>
using namespace std;

struct SAM {
  struct State { int next[26]; int link=-1; int len=0; long long occ=0; State(){ memset(next,-1,sizeof(next)); } };
  vector<State> st; int last; SAM(){ st.reserve(1<<20); st.push_back(State()); last=0; }
  void add(char cc){ int c=cc-'a'; int cur=st.size(); st.push_back(State()); st[cur].len=st[last].len+1; st[cur].occ=1; int p=last; for(; p!=-1 && st[p].next[c]==-1; p=st[p].link) st[p].next[c]=cur; if(p==-1) st[cur].link=0; else { int q=st[p].next[c]; if(st[p].len+1==st[q].len) st[cur].link=q; else { int clone=st.size(); st.push_back(st[q]); st[clone].len=st[p].len+1; st[clone].occ=0; for(; p!=-1 && st[p].next[c]==q; p=st[p].link) st[p].next[c]=clone; st[q].link=st[cur].link=clone; } } last=cur; }
  long long count_distinct(){ vector<int> cnt(st.size()+1,0), order(st.size()); for(auto &s: st) cnt[s.len]++; for(size_t i=1;i<cnt.size();++i) cnt[i]+=cnt[i-1]; for(int i=(int)st.size()-1;i>=0;--i) order[--cnt[st[i].len]]=i; long long res=0; for(int v: order) if(v) res += st[v].len - st[st[v].link].len; return res; }
  void build_occ(){ vector<int> cnt(st.size()+1,0), order(st.size()); for(auto &s: st) cnt[s.len]++; for(size_t i=1;i<cnt.size();++i) cnt[i]+=cnt[i-1]; for(int i=(int)st.size()-1;i>=0;--i) order[--cnt[st[i].len]]=i; for(int i=(int)order.size()-1;i>0;--i){ int v=order[i]; st[st[v].link].occ += st[v].occ; } }
};

