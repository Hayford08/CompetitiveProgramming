#include <iostream>
#include <vector>
using namespace std;

#define int long long
constexpr int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
vector<int> arr(MAXN);
vector<int> sum(MAXN);
int n, ans, res;

void dfs(int u, int par = -1, int d = 0){
  res += d * arr[u];

  for (auto &v : adj[u]){
    if (v == par){
      continue;
    }
    dfs(v, u, d + 1);
    sum[u] += sum[v];
  }
}


void reroot(int u, int par = -1){
  ans = max(ans, res);

  for (auto &v : adj[u]){
    if (v == par){
      continue;
    }
    res -= sum[v];
    sum[u] -= sum[v];
    res += sum[u];
    sum[v] += sum[u];

    reroot(v, u);

    sum[v] -= sum[u];
    res -= sum[u];
    sum[u] += sum[v];
    res += sum[v];  
  }
}
