#include <bits/stdc++.h>
using namespace std;

struct Dinic {
  struct Edge {
    int u, v;
    long long cap, flow;
    
    Edge(int u, int v, long long cap) : u(u), v(v), cap(cap), flow(0) {}

    inline long long capacity() const {
      return cap - flow;
    }
  };

  const long long INF = 4e18;
  vector<Edge> edges;
  vector<vector<int>> adj;
  vector<int> level, nextEdge;
  queue<int> q;
  int n, m, s, t;

  Dinic(int n, int s, int t) : n(n), m(0), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    nextEdge.resize(n);
  }

  inline void addEdge(int u, int v, long long cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0ll); // for undirected: (v, u, cap) 
    adj[u].push_back(m);
    adj[v].push_back(m + 1);
    m += 2;
  }

  inline bool reachable() {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    q.push(s);

    while (q.size()) {
      int u = q.front(); q.pop();
      int lvl = level[u];
      for (int e : adj[u]) {
        int v = edges[e].v;
        if (level[v] == -1 && edges[e].capacity() > 0) {
          level[v] = lvl + 1;
          q.push(v);
        }
      }
    }
    return level[t] != -1;
  }

  inline long long dfs(int u, long long pushed) {
    if (u == t || pushed == 0) {
      return pushed;
    }
    int lvl = level[u];
    for (int sz = adj[u].size(), &nxt = nextEdge[u]; nxt < sz; nxt++) {
      int e = adj[u][nxt];
      int v = edges[e].v;
      if (lvl + 1 != level[v]) continue;
      long long f = dfs(v, min(pushed, edges[e].capacity()));
      if (f > 0) {
        edges[e].flow += f;
        edges[e ^ 1].flow -= f;
        return f;
      }
    }
    return 0;
  }

  inline long long flow() {
    long long res = 0;
    while (reachable()) {
      fill(nextEdge.begin(), nextEdge.end(), 0);
      while (long long f = dfs(s, INF)) {
        res += f;
      }
    }
    return res;
  }

  inline pair<long long, vector<pair<int, int>>> minCuts() {
    long long f = flow();
    reachable();
    vector<pair<int, int>> cuts;
    for (const auto &edge : edges) {
      if (edge.capacity() == 0 && level[edge.u] != -1 && level[edge.v] == -1) {
        cuts.emplace_back(edge.u, edge.v);
      }
    }
    return {f, cuts};
  }

  inline vector<pair<int, int>> maxBiMatching(int l, int r) {
    flow();
    vector<pair<int, int>> res;
    for (const auto &edge : edges) {
      if (l <= edge.u && edge.u <= r && edge.flow == 1) {
        res.emplace_back(edge.u, edge.v);
      }
    }
    return res;
  }

  inline pair<long long, vector<vector<int>>> flowPaths() {
    auto f = flow();
    vector<vector<int>> paths;
    vector<pair<int, long long>> parent(n);
    while (true) {
      fill(parent.begin(), parent.end(), make_pair(-1, INF));
      parent[s] = {-2, INF};
      q.push(s);
      while (q.size()) {
        auto u = q.front(); q.pop();
        long long bneck = parent[u].second;
        for (int e : adj[u]) {
          int v = edges[e].v;
          if (edges[e].flow <= 0 || parent[v].first != -1) continue;
          parent[v] = {e, min(bneck, edges[e].flow)};
          q.push(v);
        }
      }
      if (parent[t].first == -1) break;
      vector<int> path = {t};
      int v = t;
      auto bneck = parent[v].second;
      while (v != s) {
        int e = parent[v].first;
        edges[e].flow -= bneck;
        v = edges[e].u;
        path.emplace_back(v);
      }
      reverse(path.begin(), path.end());
      paths.emplace_back(path);
    }
    return {f, paths};
  }

};