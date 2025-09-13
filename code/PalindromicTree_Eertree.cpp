/*
  Palindromic Tree (Eertree) - all palindromic substrings
  - add(char), maintains tree of palindromic substrings with links
*/

#include <bits/stdc++.h>
using namespace std;

struct Eertree {
  struct Node { int len, link; int next[26]; long long occ; Node(int l=0): len(l), link(0), occ(0){ memset(next,-1,sizeof(next)); } };
  vector<Node> t; string s; int suff; // largest suffix-palindrome node
  Eertree(){ t.push_back(Node(-1)); t.push_back(Node(0)); t[0].link=0; t[1].link=0; suff=1; }
  void add(char cc){ int c=cc-'a'; s+=cc; int pos=s.size()-1; int cur=suff; while(true){ int l=t[cur].len; if(pos-1-l>=0 && s[pos-1-l]==cc) break; cur=t[cur].link; } if(t[cur].next[c]!=-1){ suff=t[cur].next[c]; t[suff].occ++; return; } int nw=t.size(); t.push_back(Node(t[cur].len+2)); t[cur].next[c]=nw; if(t[nw].len==1){ t[nw].link=1; } else { int link=t[cur].link; while(true){ int l=t[link].len; if(pos-1-l>=0 && s[pos-1-l]==cc) { t[nw].link=t[link].next[c]; break; } link=t[link].link; } } suff=nw; t[nw].occ=1; }
  void build_occ(){ for(int i=(int)t.size()-1;i>=2;--i) t[t[i].link].occ += t[i].occ; }
};
