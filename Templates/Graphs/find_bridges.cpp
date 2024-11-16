#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin, low, subtree_size;
int timer, n;

void IS_BRIDGE(int u, int v);

inline int dfs(int u, int par = -1) {
  visited[u] = true;
  tin[u] = low[u] = timer++;
  int sz = 1;

  bool parent_skipped = false;

  for (int v : adj[u]) {
    if (v == par && !parent_skipped) {
      parent_skipped = true;
      continue;
    }

    if (visited[v]) {
      low[u] = min(low[u], tin[v]);
    }
    else {
      sz += dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > tin[u]) {
        IS_BRIDGE(u, v);
      }
    }
  }
  subtree_size[u] = sz;
}

inline void find_bridges(){
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);
  
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i);
    }
  }
}