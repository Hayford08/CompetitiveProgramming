#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN = 100;

int subtree_size[MAXN];
vector<int> adj[MAXN];

int get_subtree_size(int u, int par = -1){
  int cnt = 1;
  for (auto &v : adj[u]){
    if (v == par){
      continue;
    }
    cnt += get_subtree_size(v, u);
  }
  return subtree_size[u] = cnt;
}

int centroid(int u, int sz, int par = -1){
  for (auto &v : adj[u]){
    if (v == par){
      continue;
    }
    if (subtree_size[v] * 2 > sz){
      return centroid(v, sz, u);
    }
  }
  return u;
}
