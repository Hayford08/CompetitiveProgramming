#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, LG = 20; // N = number of nodes, LG = log2(N) + 1 

struct BinaryLift {
  vector<vector<int>> adj;
  vector<vector<int>> up;
  vector<int> tin, tout;
  int n, LG, timer;

  BinaryLift(const vector<vector<int>> &adj, int root = 0) : adj(adj) {
    n = adj.size();
    LG = ceil(log2(n)) + 1;
    up.assign(n, vector<int>(LG));
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    dfs(root, root);
  }

  inline void dfs(int u, int par) {
    tin[u] = ++timer;
    up[u][0] = par;
    // 2^i = 2^(i-1) + 2^(i-1)
    // ancestor of 2^(i-1) and then ancestor of 2^(i-1)
    for (int i = 1; i < LG; i++) {
      int anc = up[u][i - 1];
      up[u][i] = up[anc][i - 1]; 
    }

    for (auto &v : adj[u]) {
      if (v != par) {
        dfs(v, u);
      }
    }
    tout[u] = ++timer;
  }

  inline bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }

  inline int lca(int u, int v) {
    if (is_ancestor(u, v)){
      return u;
    }
    if (is_ancestor(v, u)){
      return v;
    }
    for (int i = LG - 1; i >= 0; i--) {
      if (!is_ancestor(up[u][i], v)) {
        u = up[u][i];
      }
    }
    return up[u][0];
  }
};


struct BinLift {
  int n, LOG;
  vector<vector<int>> adj;
  // par of node, depth from parent offset by level from root
  vector<vector<pair<int, int>>> binup;
  vector<array<int, 3>> subtree;
  bool precomputed = false;
  const int DEFAULT = -1e9;

  BinLift(int n) : n(n) {
    adj.resize(n);
    LOG = ceil(log2(n)) + 1;
    binup.assign(n, vector<pair<int, int>>(LOG));
    subtree.resize(n);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  inline pair<int, int> compute_depths(int u, int par, int lvl = 0) {
    int mx1 = 0, mx2 = 0;
    for (auto &v : adj[u]) {
      if (v == par) continue;
      auto [d1, d2] = compute_depths(v, u, lvl + 1);
      if (d1 + 1 > mx1) {
        mx2 = mx1;
        mx1 = d1 + 1;
      }
      else if (d1 + 1 > mx2) {
        mx2 = d1 + 1;
      }
    }
    subtree[u] = {mx1, mx2, lvl};
    return {mx1, mx2};
  }

  inline int func(int a, int b) {
    return max(a, b);
  }

  inline void compute_binup(int u, int par) {
    auto [mx1, mx2, lvl] = subtree[par];
    binup[u][0] = {par, mx1};
    if (mx1 == subtree[u][0] + 1) {
      binup[u][0].second = mx2;
    }
    binup[u][0].second -= lvl; // offset by level from root
    for (int i = 1; i < LOG; i++) {
      auto [anc, d] = binup[u][i - 1];
      binup[u][i] = {binup[anc][i - 1].first, func(d, binup[anc][i - 1].second)};
    }

    for (auto &v : adj[u]) {
      if (v == par) continue;
      compute_binup(v, u);
    }
  }

  inline void check_and_compute() {
    if (!precomputed) {
      compute_depths(0, 0);
      compute_binup(0, 0);
      precomputed = true;
    }
  }

  inline int query(int u, int k) {
    check_and_compute();
    auto [mx1, mx2, lvl] = subtree[u];
    k = min(k, lvl);
    int res = DEFAULT;
    for (int i = LOG - 1; i >= 0; i--){
      int jump = 1 << i;
      if (jump <= k) {
        res = func(res, binup[u][i].second);
        u = binup[u][i].first;
        k -= jump;
      }
    }
    return func(mx1, res + lvl); // offset by level from root
  }

  inline int lca(int u, int v) {
    check_and_compute();
    if (subtree[u][2] < subtree[v][2]) {
      swap(u, v);
    }
    int diff = subtree[u][2] - subtree[v][2];
    for (int i = 0; i < LOG; i++) {
      if (diff & (1 << i)) {
        u = binup[u][i].first;
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = LOG - 1; i >= 0; i--) {
      if (binup[u][i].first != binup[v][i].first) {
        u = binup[u][i].first;
        v = binup[v][i].first;
      }
    }
    return binup[u][0].first;
  }

  inline int distance(int u, int v) {
    check_and_compute();
    return subtree[u][2] + subtree[v][2] - 2 * subtree[lca(u, v)][2];
  }

  inline int kth_ancestor(int u, int k) {
    check_and_compute();
    int lvl = subtree[u][2];
    if (k > lvl) {
      return -1;
    }
    for (int i = 0; i < LOG; i++) {
      if (k & (1 << i)) {
        u = binup[u][i].first;
      }
    }
    return u;
  }
};

