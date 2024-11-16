#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Expects a permutation of the numbers from 0 to n - 1.
int run(const vector<int> &perm) {
  int n = perm.size();
  vector<int> adj(n);
  for (int i = 0; i < n; i++) {
    adj[i] = perm[i];
  }
  vector<bool> vis(n);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (vis[i]) {
      continue;
    }
    int cur = i;
    // Find the cycle containing i.
    int len = 0;
    vector<int> cycle;
    while (!vis[cur]) {
      cycle.push_back(cur);
      vis[cur] = true;
      cur = adj[cur];
      len++;
    }
    // do something with the cycle
    ans += (len - 1) / 2;
  }
  return ans;
}

// no need for adj 
int run2(const vector<int> &perm) {
  int n = perm.size();
  vector<bool> vis(n);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (vis[i]) {
      continue;
    }
    int cur = i;
    // Find the cycle containing i.
    int len = 0;
    vector<int> cycle;
    while (!vis[cur]) {
      cycle.push_back(cur);
      vis[cur] = true;
      cur = perm[cur];
      len++;
    }
    // do something with the cycle
    ans += (len - 1) / 2;
  }
  return ans;
}