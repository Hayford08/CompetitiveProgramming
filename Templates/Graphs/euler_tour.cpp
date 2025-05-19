
#include <bits/stdc++.h>
using namespace std;

int n;

vector<vector<int>> adj(n);
vector<pair<int, int>> euler(n);
int timer = 0;
inline void dfs(int u, int par) {
  euler[u].first = ++timer;
  for (auto &v : adj[u]) {
    if (v == par) continue;
    dfs(v, u);
  }
  euler[u].second = timer;
}
