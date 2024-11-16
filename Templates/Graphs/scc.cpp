#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> g, rev_g;
vector<bool> visited;
vector<int> order, component;

void dfs1(int u){
  visited[u] = true;
  for (int v : g[u]){
    if (!visited[v]){
      dfs1(v);
    }
  }
  order.push_back(u);
}

void dfs2(int u){
  visited[u] = true;
  component.push_back(u);
  for (int v : rev_g[u]){
    if (!visited[v]){
      dfs2(v);
    }
  }
}

void create_scc(int n){
  for (;;){
    int u, v;
    // get the edge
    g[u].push_back(v);
    rev_g[v].push_back(u);
  }

  visited.assign(n, false);
  for (int u = 0; u < n; u++){
    if (!visited[u]){
      dfs1(u);
    }
  }
  visited.assign(n, false);
  reverse(order.begin(), order.end());
  for (int u : order){
    if (!visited[u]){
      dfs2(u);
      // do other stuff -- refer to create condensed graph

      component.clear();
    }
  }
}

void create_condensed_graph(int n){
  vector<bool> visited(n);
  vector<int> roots(n);
  vector<int> root_nodes; // list of all roots in the new graph
  vector<vector<int>> adj_scc(n);
  // do regular kusaraju-sharir and then ...
  for (auto &u : order){
    if (!visited[u]){
      dfs2(u);
      int root = component.front();
      for (auto &v : component){
        roots[v] = root;
      }
      root_nodes.push_back(root);
      component.clear();
    }
  }
  for (int u = 0; u < n; u++){
    for (auto v : g[u]){
      int root_u = roots[u], root_v = roots[v];
      if (root_u != root_v){
        adj_scc[root_u].push_back(root_v);
      }
    }
  }
  // now do something with add
}

