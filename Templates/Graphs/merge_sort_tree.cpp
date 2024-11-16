#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// Model problem: answer queries based on [l, r, x] and find the smallest element within [l, r] >= x

struct MergeSortTree{
  private: 
    int n;
    vector<vector<int>> tree;
    const int INF = 1e9;

    void combine(vector<int> &lval, vector<int> &rval, vector<int> &root) {
      merge(lval.begin(), lval.end(), 
            rval.begin(), rval.end(),
            back_inserter(root));
    }

    // O(nlogn)
    void build(vector<int> &arr, int tidx, int tl, int tr){
      if (tl == tr){
        tree[tidx] = {arr[tl]};
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      build(arr, lchild, tl, tm);
      build(arr, rchild, tm + 1, tr);
      combine(tree[lchild], tree[rchild], tree[tidx]);
    }

    // O(log2n)
    int range_query(int tidx, int tl, int tr, int l, int r, int x){
      if (l > tr || tl > r){
        return INF;
      }
      if (l <= tl && tr <= r){
        auto it = lower_bound(tree[tidx].begin(), tree[tidx].end(), x);
        if (it != tree[tidx].end()){
          return *it;
        }
        return INF;
      }
      int tm = tl + (tr - tl) / 2;
      return min(range_query(tidx + 1, tl, tm, l, min(r, tm), x),
                 range_query(tidx + 2 * (tm - tl + 1), tm + 1, tr, max(l, tm + 1), r, x));
    }

  public:
    MergeSortTree(vector<int> &arr) : n((int)arr.size()), tree(2 * (int)arr.size()) {
      build(arr, 0, 0, n - 1);
    }

    int range_query(int l, int r, int x){
      return range_query(0, 0, n - 1, l , r, x);
    }
};

struct MergeSortTreeWithUpdate {
private:
  int n;
  vector<multiset<int>> tree;
  vector<int> arr;
  const int INF = 1e9;

  void combine(multiset<int> &lval, multiset<int> &rval, multiset<int> &root) {
    merge(lval.begin(), lval.end(), 
          rval.begin(), rval.end(),
          back_inserter(root));
  }

  // TC: O(nlog2n)
  void build(vector<int> &arr, int tidx, int tl, int tr){
    if (tl == tr){
      tree[tidx] = {arr[tl]};
      return;
    }
    int tm = tl + (tr - tl) / 2;
    int lchild = tidx + 1; 
    int rchild = tidx + 2 * (tm - tl + 1);
    build(arr, lchild, tl, tm);
    build(arr, rchild, tm + 1, tr);
    combine(tree[lchild], tree[rchild], tree[tidx]);
  }

  // O(log2n)
  void point_update(int tidx, int tl, int tr, int pos, int val){
    auto it = tree[tidx].find(arr[pos]);
    tree[tidx].erase(it);
    tree[tidx].insert(val);

    if (tl == tr){
      arr[pos] = val;
      return;
    }
    int tm = tl + (tr - tl) / 2;
    if (pos <= tm){
      point_update(tidx + 1, tl, tm, pos, val);
    }
    else {
      point_update(tidx + 2 * (tm - tl + 1), tm + 1, tr, pos, val);
    }
  }

  int range_query(int tidx, int tl, int tr, int l, int r, int x){
    if (l > tr || tl > r) {
      return INF;
    }
    if (l <= tl && tr <= r){
      auto it = tree[tidx].lower_bound(x);
      if (it != tree[tidx].end()){
        return *it;
      }
      return INF;
    }
    int tm = tl + (tr - tl) / 2;
    return min(range_query(tidx + 1, tl, tm, l, min(r, tm), x),
               range_query(tidx + 2 * (tm - tl + 1), tm + 1, tr, max(l, tm + 1), r, x));
  }

public:
  MergeSortTreeWithUpdate(vector<int> &arr) : n((int)arr.size()), tree(2 * (int)arr.size()), arr(arr) {

  }

  void point_update(int pos, int val){
    point_update(0, 0, n - 1, pos, val);
  }

  int range_query(int l, int r, int x){
    return range_query(0, 0, n - 1, l, r, x);
  }
};