#include <bits/stdc++.h>
using namespace std;

struct SCC {
  int n;
  vector<vector<int>> adj, rev_adj;
  vector<bool> visited;
  vector<int> order;
  vector<int> components;
  int num_components;

  SCC(int n) : n(n), adj(n), rev_adj(n), visited(n, false), components(n, -1), num_components(-1) {}

  // Add a directed edge u -> v
  inline void addEdge(int u, int v) {
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
  }

  // First DFS pass on the original graph to determine the exit order
  inline void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
      if (visited[v]) continue;
      dfs1(v);
    }
    order.push_back(u);
  }

  // Second DFS pass on the transpose graph to mark SCCs
  inline void dfs2(int u, int id) {
    components[u] = id;
    for (int v : rev_adj[u]) {
      if (components[v] == -1) {
        dfs2(v, id);
      }
    }
  }

  // Runs the Kosaraju algorithm
  // Returns the total number of strongly connected components.
  inline int buildSCC() {
    if (num_components != -1) {
      return num_components;
    }

    // 1) Run DFS on original graph to get ordering by exit time
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        dfs1(i);
      }
    }

    // 2) Process vertices in decreasing order of exit times
    reverse(order.begin(), order.end());

    // 3) Run DFS on the transpose graph in that order
    num_components = 0;
    for (int v : order) {
      if (components[v] == -1) {
        dfs2(v, num_components);
        num_components++;
      }
    }
    return num_components;
  }

  // Returns a vector of components, where each component contains
  // the vertices in that component.
  inline vector<vector<int>> getComponents() {
    if (num_components == -1) {
      buildSCC();
    }
    vector<vector<int>> comps(num_components);
    for (int v = 0; v < n; v++) {
      comps[components[v]].push_back(v);
    }
    return comps;
  }

  // Builds a condensed graph where each vertex represents an SCC.
  inline vector<vector<int>> getCondensedGraph() {
    if (num_components == -1) {
      buildSCC();
    }
    vector<vector<int>> adj_cond(num_components);
    for (int u = 0; u < n; u++) {
      int root_u = components[u];
      for (int v : adj[u]) {
        int root_v = components[v];
        if (root_u != root_v) {
          adj_cond[root_u].push_back(root_v);
        }
      }
    }
    return adj_cond;
  }

  inline array<int, 2> pairWithNoPath() {
    vector<bool> visited(n, false);
    dfs(0, adj, visited);
    for (int i = 0; i < n; i++) {
      if (visited[i]) continue;
      return {0, i};
    } 
    visited.assign(n, false);
    dfs(0, rev_adj, visited);
    for (int i = 0; i < n; i++) {
      if (visited[i]) continue;
      return {i, 0};
    }
    return {-1, -1};
  }

private:
  // performs a DFS from a given vertex
  inline void dfs(int u, vector<vector<int>> &adj, vector<bool> &visited) {
    vector<int> stack = {u};
    visited[u] = true;
    while (stack.size()) {
      u = stack.back();
      stack.pop_back();
      for (int v : adj[u]) {
        if (!visited[v]) {
          visited[v] = true;
          stack.push_back(v);
        }
      }
    }
  }
};
