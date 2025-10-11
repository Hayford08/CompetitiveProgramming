#include <bits/stdc++.h>
using namespace std;

constexpr long long INF = 4e18;

struct MaxFlow {
  vector<vector<int>> adj;
  vector<vector<long long>> capacity, rCapacity;
  vector<int> parent;
  set<pair<int, int>> edges;
  int s, t;

  MaxFlow(int n, int s, int t) : adj(n), capacity(n, vector<long long>(n)), rCapacity(n, vector<long long>(n)), parent(n), s(s), t(t) {}

  void add(int u, int v, int c) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.insert({u, v});
    capacity[u][v] += c;
    // capacity[v][u] += c // for undirected graph
  }

  long long bfs() {
    ranges::fill(parent, -1);
    parent[s] = -2;

    queue<pair<long long, int>> q;
    q.push({INF, s});

    while (q.size()) {
      auto [flow, u] = q.front(); q.pop();
      for (int v : adj[u]) {
        if (parent[v] == -1 && capacity[u][v] > 0) {
          parent[v] = u;
          long long nflow = min(flow, capacity[u][v]);
          if (v == t) {
            return nflow;
          }
          q.push({nflow, v});
        }
      }
    }
    return 0ll;
  }

  long long flow() {
    long long maxFlow = 0, currFlow = 0;
    while ((currFlow = bfs()) > 0) {
      maxFlow += currFlow;
      int curr = t;
      while (curr != s) {
        int pv = parent[curr];
        capacity[pv][curr] -= currFlow;
        capacity[curr][pv] += currFlow;

        rCapacity[pv][curr] += currFlow;
        rCapacity[curr][pv] -= currFlow;
        curr = pv;
      }
    }
    return maxFlow;
  }

  pair<long long, vector<pair<int, int>>> minCuts(int s, int t) {
    long long maxFlow = flow();
    bfs();
    vector<pair<int, int>> cuts;
    for (const auto &[u, v] : edges) {
      int cnt = (parent[u] == -1) + (parent[v] == -1);
      if (cnt == 1) {
        cuts.push_back({u, v});
      }
    }
    return {maxFlow, cuts};
  }

  pair<long long, vector<vector<int>>> maxFlowWithPaths(int s, int t) {
    long long maxFlow = flow();
    vector<vector<int>> paths;
    capacity = rCapacity;
    long long flow = 0;
    while ((flow = bfs()) > 0) {
      vector<int> path = {t};
      int v = t;
      while (v != s) {
        int u = parent[v];
        capacity[u][v] -= flow;
        v = u;
        path.push_back(v);
      }
      ranges::reverse(path);
      paths.push_back(path);
    }
    return {maxFlow, paths};
  }

  inline vector<pair<int, int>> maxBipartiteMatching(int l, int r) {
    flow();
    vector<pair<int, int>> res;
    for (const auto &[u, v] : edges) {
      if (l <= u && u <= r && capacity[u][v] == 0) {
        res.emplace_back(u, v);
      }
    }
    return res;
  }

};
