/*
  Hopcroft-Karp (Maximum Bipartite Matching)
  - Left part: 0..nL-1, Right part: 0..nR-1
  - addEdge(u, v): u in [0, nL), v in [0, nR)
  - maxMatching(): returns maximum matching size
  Complexity: O(E * sqrt(V)).
*/

#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
  int nL, nR;
  vector<vector<int>> adj; // adj[u] -> neighbors v on right
  vector<int> matchL, matchR, dist;

  HopcroftKarp(int nL, int nR) : nL(nL), nR(nR), adj(nL), matchL(nL, -1), matchR(nR, -1), dist(nL, -1) {}

  void addEdge(int u, int v) { // 0 <= u < nL, 0 <= v < nR
    adj[u].push_back(v);
  }

  bool bfs() {
    queue<int> q;
    fill(dist.begin(), dist.end(), -1);
    bool reachableFreeRight = false;
    for (int u = 0; u < nL; ++u) if (matchL[u] == -1) { dist[u] = 0; q.push(u); }
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        int u2 = matchR[v];
        if (u2 == -1) reachableFreeRight = true; // we can end on a free right node
        else if (dist[u2] == -1) { dist[u2] = dist[u] + 1; q.push(u2); }
      }
    }
    return reachableFreeRight;
  }

  bool dfs(int u) {
    for (int v : adj[u]) {
      int u2 = matchR[v];
      if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
        matchL[u] = v; matchR[v] = u; return true;
      }
    }
    dist[u] = -1; // mark as dead end in this layering
    return false;
  }

  int maxMatching() {
    int res = 0;
    while (bfs()) {
      for (int u = 0; u < nL; ++u)
        if (matchL[u] == -1 && dfs(u)) ++res;
    }
    return res;
  }
};

// Example usage:
// int main() {
//   int nL = 3, nR = 3; HopcroftKarp HK(nL, nR);
//   HK.addEdge(0, 0); HK.addEdge(0, 1); HK.addEdge(1, 1); HK.addEdge(2, 2);
//   cout << HK.maxMatching() << "\n"; // expected 3
// }

