#include <iostream>
#include <vector>
using namespace std;


// Model problem: Finding the subsegment with the maximal sum i.e. Kadane's algorithm and allow for point updates.
constexpr long long DEFAULT = -1e18;
struct Node {
  long long total, pref, suff, best;
  Node() : total(0), pref(DEFAULT), suff(DEFAULT), best(DEFAULT) {}
  Node(long long val) : total(val), pref(val), suff(val), best(val) {}
};

struct SegmentTree {
  int n;
  vector<Node> tree;

  inline Node combine(Node l, Node r) {
    Node ans;
    ans.total = l.total + r.total;
    ans.pref = max(l.pref, l.total + r.pref);
    ans.suff = max(r.suff, l.suff + r.total);
    ans.best = max({l.best, r.best, ans.pref, ans.suff, l.suff + r.pref});
    return ans;
  }

  inline void build(vector<int> &arr, int tidx, int tl, int tr) {
    if (tl == tr) {
        tree[tidx] = Node(arr[tl]);
        return;
    }
    int tm = tl + (tr - tl) / 2;
    int lchild = tidx + 1;
    int rchild = tidx + 2 * (tm - tl + 1);
    build(arr, lchild, tl, tm);
    build(arr, rchild, tm + 1, tr);
    tree[tidx] = combine(tree[lchild], tree[rchild]);
  }

  inline void point_update(int tidx, int tl, int tr, int pos, int val) {
    if (pos < tl || pos > tr) return;
    if (tl == tr) {
      tree[tidx] = Node(val);
      return;
    }
    int tm = tl + (tr - tl) / 2;
    int lchild = tidx + 1;
    int rchild = tidx + 2 * (tm - tl + 1);
    if (pos <= tm) {
      point_update(lchild, tl, tm, pos, val);
    } else {
      point_update(rchild, tm + 1, tr, pos, val);
    }
    tree[tidx] = combine(tree[lchild], tree[rchild]);
  }

  inline Node range_query(int tidx, int tl, int tr, int l, int r) {
    if (l > tr || tl > r) {
      return Node();
    }
    if (l <= tl && tr <= r) {
      return tree[tidx];
    }
    int tm = tl + (tr - tl) / 2;
    return combine(range_query(tidx + 1, tl, tm, l, min(tm, r)),
                   range_query(tidx + 2 * (tm - tl + 1), tm + 1, tr, max(l, tm + 1), r));
  }

  SegmentTree(vector<int> &arr): n((int)arr.size()), tree(2 * n + 1) {
    build(arr, 0, 0, n - 1);
  }

  inline void point_update(int pos, int val) {
    point_update(0, 0, n - 1, pos, val);
  }

  inline Node range_query(int l, int r) {
    return range_query(0, 0, n - 1, l, r);
  }
};
