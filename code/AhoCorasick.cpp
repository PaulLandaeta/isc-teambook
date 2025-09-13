/*
  Aho-Corasick automaton (multiple pattern matching)
  - Builds a trie of patterns with failure links (BFS)
  - search(text) returns, for each pattern, all starting indices where it occurs

  Usage:
    vector<string> patterns = {"he", "she", "his", "hers"};
    AhoCorasick ac(patterns);
    auto occ = ac.search("ahishers");
  // occ[i] are the starting indices of patterns[i] in the text
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
  // trie edges by character
  unordered_map<char, Node*> next;
  // suffix link (failure link)
  Node* link = nullptr;
  // output link to next terminal node on the suffix chain
  Node* out = nullptr;
  // parent and incoming char (useful for building links)
  Node* parent = nullptr;
  char ch = 0;
  // if terminal: id of the pattern ending here, else -1
  int patId = -1;
};

struct AhoCorasick {
  Node* root;
  vector<string> pats;
  vector<Node*> nodes; // to free

  AhoCorasick(const vector<string>& patterns) : root(new Node()), pats(patterns) {
    nodes.push_back(root);
    for (int i = 0; i < (int)pats.size(); ++i) insert(pats[i], i);
    build();
  }

  ~AhoCorasick() { // simple deletion
    for (Node* n : nodes) delete n;
  }

  void insert(const string& s, int id) {
    Node* cur = root;
    for (char c : s) {
      auto it = cur->next.find(c);
      if (it == cur->next.end()) {
        Node* nx = new Node();
        nx->parent = cur; nx->ch = c;
        nodes.push_back(nx);
        cur->next[c] = nx;
        cur = nx;
      } else cur = it->second;
    }
    cur->patId = id;
  }

  void build() {
    queue<Node*> q;
    // root's direct children: link to root
    root->link = root; root->out = nullptr;
    for (auto& kv : root->next) {
      kv.second->link = root;
      kv.second->out = (kv.second->patId != -1) ? kv.second : nullptr;
      q.push(kv.second);
    }
    // BFS
    while (!q.empty()) {
      Node* v = q.front(); q.pop();
      for (auto& kv : v->next) {
        char c = kv.first; Node* u = kv.second; q.push(u);
        // compute failure link
        Node* f = v->link;
        while (f != root && !hasEdge(f, c)) f = f->link;
        if (hasEdge(f, c) && f->next[c] != u) f = f->next[c];
        u->link = (hasEdge(f, c) ? f : root);
        // compute output link: nearest terminal on suffix chain
        if (u->patId != -1) u->out = u; else u->out = u->link->out;
      }
    }
  }

  static inline bool hasEdge(Node* n, char c) { return n->next.find(c) != n->next.end(); }

  vector<vector<int>> search(const string& text) const {
    vector<vector<int>> res(pats.size());
    Node* cur = root;
    for (int i = 0; i < (int)text.size(); ++i) {
      char c = text[i];
      while (cur != root && !hasEdge(cur, c)) cur = cur->link;
      if (hasEdge(cur, c)) cur = cur->next.at(c);
      // report all matches at this state via out links
      for (Node* t = (cur->patId != -1 ? cur : cur->out); t; t = (t->out && t->out != t ? t->out : nullptr)) {
        int id = t->patId;
        if (id != -1) res[id].push_back(i - (int)pats[id].size() + 1);
      }
    }
    return res;
  }
};

// Example usage
// int main() {
//   vector<string> patterns = {"he", "she", "his", "hers"};
//   string text = "ahishers";
//   AhoCorasick ac(patterns);
//   auto occ = ac.search(text);
//   for (int i = 0; i < (int)patterns.size(); ++i) {
//     cout << patterns[i] << ": ";
//     for (int p : occ[i]) cout << p << ' ';
//     cout << '\n';
//   }
// }
