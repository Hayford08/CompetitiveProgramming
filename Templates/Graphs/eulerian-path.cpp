#include "bits/stdc++.h"

using namespace std;

vector<vector<int>> find_eulerian_path(const vector<vector<int>>& pairs) {
  int n = pairs.size();
  unordered_map<int, queue<int>> adj;
  unordered_map<int, int> indeg, outdeg;
  for (auto &pair : pairs) {
      int u = pair[0], v = pair[1];
      adj[u].push(v);
      indeg[v]++;
      outdeg[u]++;
  }

  int u = pairs[0][0];
  for (auto &[k, v] : outdeg) {
      if (v == indeg[k] + 1) {
          u = k;
          break;
      }
  }

  vector<int> order;
  vector<int> stk = {u};

  while (stk.size()) {
      u = stk.back(); 
      auto it = adj.find(u);
      if (it == adj.end()) {
          order.push_back(u);
          stk.pop_back();
      }
      else {
          int v = it->second.front(); it->second.pop();
          if (it->second.empty()){
              adj.erase(it);
          }
          stk.push_back(v);
      }
  }

  reverse(order.begin(), order.end());
  vector<vector<int>> res;
  for (int i = 1, sz = order.size(); i < sz; i++){
      res.push_back({order[i - 1], order[i]});
  }
  return res;
}