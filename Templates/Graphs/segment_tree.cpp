#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template <class T>
class SegmentTree {
private:
  const T DEFAULT = 1e9;
  int len;
  std::vector<T> segtree;
  vector<int> arr;

  // Function to build the segment tree
  void build(int tIdx, int l, int r) {
    if (l == r) {
        segtree[tIdx] = arr[l];
        return;
    }
    int m = l + (r - l) / 2;
    int lc = tIdx + 1;
    int rc = tIdx + 2 * (m - l + 1);
    build(lc, l, m);
    build(rc, m + 1, r);
    segtree[tIdx] = combine(segtree[lc], segtree[rc]);
  }

  void point_update(int ind, T val, int tidx, int tl, int tr) {
    if (tl == tr) {
      segtree[tidx] = val;
      return;
    }
    int mid = (tl + tr) / 2;
    int lchild = tidx + 1;
    int rchild = tidx + 2 * (mid - tl + 1);
    if (ind <= mid) {
      point_update(ind, val, lchild, tl, mid);
    } 
    else {
      point_update(ind, val, rchild, mid + 1, tr);
    }
    segtree[tidx] = combine(segtree[lchild], segtree[rchild]);
  }

  T combine(T left_val, T right_val){
    return std::min(left_val, right_val);
  }

  T range_query(int l, int r, int tidx, int tl, int tr) {
    if (l > tr || r < tl) {
      return DEFAULT;
    }
    if (l <= tl && tr <= r) {
      return segtree[tidx];
    }
    int tm = (tl + tr) / 2;
    int lchild = tidx + 1;
    int rchild = tidx + 2 * (tm - tl + 1);
    return combine(range_query(l, min(r, tm), lchild, tl, tm),
                   range_query(max(l, tm + 1), r, rchild, tm + 1, tr));
  }

public:
  SegmentTree(int len) : len(len), segtree(len * 2 + 1, DEFAULT) {}

  SegmentTree(vector<T> &values) : 
    len(values.size()), segtree(2 * values.size() + 1, DEFAULT), arr(values) {
      build(0, 0, len - 1);
    }

  void point_update(int ind, T val) {
    point_update(ind, val, 0, 0, len - 1);
  }

  T range_query(int l, int r) {
    return range_query(l, r, 0, 0, len - 1);
  }
};


  /*
  int find_kth(int tidx, int tl, int tr, int k){
    if (k > segtree[tidx]){
      return -1;
    }
    if (tl == tr){
      return tl;
    }
    int tm = tl + (tr - tl) / 2;
    if (segtree[tidx + 1] >= k){
      return find_kth(tidx + 1, tl, tm, k);
    }
    k -= segtree[tidx + 1];
    return find_kth(tidx + 2 * (tm - tl + 1), tm + 1, tr, k);
  }

  int find_first_gt(int tidx, int tl, int tr, int l, int r, int x){
    if (tl > r || tr < l){
      return -1;
    }
    if (segtree[tidx] <= x){
      return -1;
    }
    int tm = tl + (tr - tl) / 2;
    int res = find_first_ge(tidx + 1, tl, min(tm, r), x);
    if (res != -1){
      return res;
    } 
    return find_first_ge(tidx + 2 * (tm - tl + 1), max(l, tm + 1), tr, x);
  }

  */