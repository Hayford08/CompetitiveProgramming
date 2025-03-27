#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Merge, typename Update>
struct ReRootDp {
  const vector<vector<int>>& adj;
  vector<T> base;
  Merge merge;
  Update update;
  vector<T> res;

  ReRootDp(const vector<vector<int>>& adj, vector<T> base, Merge merge, Update update)
      : adj(adj), base(base), merge(merge), update(update), res(adj.size()) {}

    ReRootDp(const vector<vector<int>>& adj, T base, Merge merge, Update update)
      : adj(adj), base(adj.size(), base), merge(merge), update(update) {}

  inline T dfs(int u, int par = -1) {
    T curr = base[u];
    for (const int& v : adj[u]) {
      if (v == par) continue;
      curr = merge(curr, dfs(v, u));
    }
    return res[u] = curr;
  }

  inline void dfs2(int u, int par = -1) {
    for (const int& v : adj[u]) {
      if (v == par) continue;
      T nval = update(res[u], res[v]);
      res[v] = merge(res[v], nval);
      dfs2(v, u);
    }
  }

  inline void compute() {
    dfs(0);
    dfs2(0);
  }
};

// Factory functions to deduce Merge and Update types
template <typename T, typename Merge, typename Update>
ReRootDp<T, Merge, Update> make_ReRootDp(const vector<vector<int>>& adj, vector<T> base, Merge merge, Update update) {
  return ReRootDp<T, Merge, Update>(adj, base, merge, update);
}

template <typename T, typename Merge, typename Update>
ReRootDp<T, Merge, Update> make_ReRootDp(const vector<vector<int>>& adj, T base, Merge merge, Update update) {
  return ReRootDp<T, Merge, Update>(adj, base, merge, update);
}
