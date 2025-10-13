#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
	static constexpr int FREE = -1;
  int n;
  vector<vector<int>> adj;
  vector<int> match, level;
  queue<int> q;

  HopcroftKarp(int n) : n(n), adj(n), match(n, FREE), level(n) {}

	// vertex `u` on the left side and vertex `v` on the right side
  inline void addEdge(int u, int v) {
    adj[u].emplace_back(v);
  }

  // checks if there is an augmenting path starting from free nodes
  inline bool bfs() {
		fill(level.begin(), level.end(), -1);
    for (int u = 0; u < n; u++) {
			if (match[u] == FREE) {
				level[u] = 0;
				q.push(u);
			}
    }
    bool found = false;
    while (q.size()) {
      int u = q.front(); q.pop();
      int lvl = level[u];
      for (int v : adj[u]) {
				int pr = match[v];
				if (pr == FREE) {
					// found a free vertex => we can augment
					found = true;
				}
        else if (level[pr] == FREE) {
          level[pr] = lvl + 1;
          q.push(pr);
        }
      }
    }
    return found;
  }

  // checks if an augmenting path has been found from u 
  // and also adds the matching for u if found
  inline bool dfs(int u) {
		int lvl = level[u];
    for (int v : adj[u]) {
			int pr = match[v];
			if (pr == FREE || (level[pr] == lvl + 1 && dfs(pr))) {
				match[u] = v;
				match[v] = u;
				return true;
			}
    }
		level[u] = FREE;
    return false;
  }

  inline int maxMatching() {
    int cnt = 0;
    while (bfs()) {
      for (int u = 0; u < n; u++) {
        if (match[u] == FREE && dfs(u)) {
          cnt++;
        }
      }
    }
    return cnt;
  }

  inline vector<pair<int, int>> getMatching() {
    maxMatching();
    vector<pair<int, int>> res;
    vector<bool> seen(n);
    for (int u = 0; u < n; u++) {
      int v = match[u];
      if (v != FREE && !seen[u] && !seen[v]) {
        res.emplace_back(u, v);
        seen[u] = seen[v] = true;
      }
    }
    return res;
  }
};