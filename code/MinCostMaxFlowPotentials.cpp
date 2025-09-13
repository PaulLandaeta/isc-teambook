/*
  Min-Cost Max-Flow (successive shortest augmenting paths)
  - Dijkstra on residual graph with Johnson potentials to handle costs >= any value
  - Interface:
      MinCostMaxFlow mcmf(n);
      mcmf.add_edge(u, v, cap, cost);  // directed edge
      auto [flow, cost] = mcmf.min_cost_max_flow(s, t);
  - Complexity: roughly O(F * E log V), fast in practice.
*/

#include <bits/stdc++.h>
using namespace std;

struct MinCostMaxFlow {
  struct Edge { int to, rev; long long cap, cost; };
  int n; vector<vector<Edge>> g;
  MinCostMaxFlow(int n = 0) { init(n); }
  void init(int n_) { n = n_; g.assign(n, {}); }

  void add_edge(int u, int v, long long cap, long long cost) {
    Edge a{v, (int)g[v].size(), cap, cost};
    Edge b{u, (int)g[u].size(), 0,  -cost};
    g[u].push_back(a); g[v].push_back(b);
  }

  pair<long long,long long> min_cost_max_flow(int s, int t) {
    const long long INF = (1LL<<62);
    long long flow = 0, cost = 0;
    vector<long long> dist(n), pot(n, 0), add(n);
    vector<int> pv_v(n), pv_e(n);

    auto dijkstra = [&]()->bool {
      fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
      pq.push({0, s});
      while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (int i = 0; i < (int)g[u].size(); ++i) {
          const Edge &e = g[u][i]; if (e.cap <= 0) continue;
          long long w = e.cost + pot[u] - pot[e.to];
          if (dist[e.to] > d + w) {
            dist[e.to] = d + w; pv_v[e.to] = u; pv_e[e.to] = i;
            pq.push({dist[e.to], e.to});
          }
        }
      }
      if (dist[t] == INF) return false;
      for (int v = 0; v < n; ++v) if (dist[v] < INF) pot[v] += dist[v];
      return true;
    };

    while (dijkstra()) {
      long long push = INF;
      for (int v = t; v != s; v = pv_v[v]) {
        Edge &e = g[pv_v[v]][pv_e[v]]; push = min(push, e.cap);
      }
      for (int v = t; v != s; v = pv_v[v]) {
        Edge &e = g[pv_v[v]][pv_e[v]]; Edge &er = g[v][e.rev];
        e.cap -= push; er.cap += push; cost += push * e.cost;
      }
      flow += push;
    }
    return {flow, cost};
  }
};

// Example usage:
// int main() {
//   MinCostMaxFlow mf(4);
//   mf.add_edge(0,1,1,1);
//   mf.add_edge(0,2,1,2);
//   mf.add_edge(1,3,1,1);
//   mf.add_edge(2,3,1,1);
//   auto [f, c] = mf.min_cost_max_flow(0,3); // f=2, c=3
//   cout << f << " " << c << "\n";
// }

