#include <bits/stdc++.h>
using namespace std;

// Bron-Kerbosch algorithm for finding all maximal cliques in an undirected graph.
// Complexity: O(3^(n/3)) in the worst case.

set<int> max_clique(vector<set<int>> &adj) {
  set<int> res;
  int n = adj.size();

  function<void(set<int>&, set<int>&, set<int>&)> bron_kerbosch = [&](set<int> &curr, set<int> &potential, set<int> &processed) {
    if (potential.empty() && processed.empty()) {
      if (curr.size() > res.size()) {
        res = curr;
      }
      return;
    }
    while (potential.size()) {
      int u = *potential.begin(); potential.erase(u);
      auto ncurr = curr; ncurr.insert(u);
      set<int> npotential, nprocessed;
      
      for (auto &v : potential) {
        if (adj[u].count(v)) {
          npotential.insert(v);
        }
      }

      for (auto &v : processed) {
        if (adj[u].count(v)) {
          nprocessed.insert(v);
        }
      }

      bron_kerbosch(ncurr, npotential, nprocessed);
      
      processed.insert(u);
    }
  };

  set<int> potential, processed, curr;
  for (int i = 0; i < n; i++) {
    potential.insert(i);
  }
  bron_kerbosch(curr, potential, processed);
  return res;
}