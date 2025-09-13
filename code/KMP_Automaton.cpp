/*
  KMP Automaton for pattern matching DP
  - build_automaton(p): next state for adding a character
*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> kmp_automaton(const string& p){
  int n=p.size(); const int A=26; vector<int> lps(n,0);
  for(int i=1;i<n;++i){ int j=lps[i-1]; while(j>0 && p[i]!=p[j]) j=lps[j-1]; if(p[i]==p[j]) j++; lps[i]=j; }
  vector<vector<int>> aut(n+1, vector<int>(A,0));
  for(int state=0;state<=n;++state){ for(int c=0;c<A;++c){ if(state<n && ('a'+c)==p[state]) aut[state][c]=state+1; else aut[state][c]=(state==0? 0 : aut[lps[state-1]][c]); } }
  return aut;
}

