#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct DSU {
  vector<int> parent, size;
  int components;
  DSU(int n) : parent(n), size(n, 1), components(n) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int a){
    if (parent[a] == a){
      return a;
    }
    return parent[a] = find(parent[a]);
  }

  inline bool merge(int a, int b){
    int parA = find(a);
    int parB = find(b);
    if (parA == parB){
      return false;
    }
    if (size[parA] < size[parB]){
      swap(parA, parB);
    }
    size[parA] += size[parB];
    parent[parB] = parA;
    components--;
    return true;
  }

  inline bool same(int a, int b){
    return find(a) == find(b);
  }

  inline vector<vector<int>> groups() {
    vector<vector<int>> res;
    int n = parent.size();
    vector<int> group(n, -1);
    for (int i = 0; i < n; i++) {
      int root = find(i);
      if (group[root] == -1) {
        group[root] = res.size();
        res.push_back({});
      }
      res[group[root]].push_back(i);
    }
    return res;
  }
};
