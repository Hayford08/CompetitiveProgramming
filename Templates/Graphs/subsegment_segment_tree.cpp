#include <iostream>
#include <vector>
using namespace std;


// Model problem: Finding the subsegment with the maximal sum

struct Node {
  int total, pref, suff, curr;
  Node() {}
  Node(int val) : total(val), pref(max(0, val)), suff(max(0, val)), curr(max(0, val)) {
  }
};

struct SegmentTree {
private:
  int n;
  vector<Node> tree;

  Node combine(Node l, Node r) {
    Node ans;
    ans.total = l.total + r.total;
    ans.pref = max(l.pref, l.total + r.pref);
    ans.suff = max(r.suff, l.suff + r.total);
    ans.curr = max({l.curr, r.curr, l.suff + l.pref});
    return ans;
  }

  void build(vector<int> &arr, int tidx, int tl, int tr) {
    if (tl == tr){
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

  void point_update(int tidx, int tl, int tr, int pos, int val) {
    if (tl == tr) {
      tree[tidx] = Node(val);
      return;
    }
    int tm = tl + (tr - tl) / 2;
    int lchild = tidx + 1;
    int rchild = tidx + 2 * (tm - tl + 1);
    if (pos <= tm) {
      point_update(lchild, tl, tm, pos, val);
    }
    else {
      point_update(rchild, tm + 1, tr, pos, val);
    }
    tree[tidx] = combine(tree[lchild], tree[rchild]);
  }

  Node range_query(int tidx, int tl, int tr, int l, int r) {
    if (l > tr || tl > r) {
      return Node(0); // base case to use
    }
    if (l <= tl && tr <= r){
      return tree[tidx];
    }
    int tm = tl + (tr - tl) / 2;
    return combine(range_query(tidx + 1, tl, tm, l, min(tm, r)),
                  range_query(tidx + 2 * (tm - tl + 1), tm + 1, tr, max(l, tm + 1), r));
  }

public:
  SegmentTree(int n) : n(n), tree(2 * n + 1) {}

  SegmentTree(vector<int> &arr) {
    n = (int)arr.size();
    tree = vector<Node>(2 * n + 1);
    build(arr, 0, 0, n - 1);
  }

  void point_update(int pos, int val) {
    point_update(0, 0, n - 1, pos, val);
  }

  Node range_query(int l, int r) {
    return range_query(0, 0, n - 1, l, r);
  }
};