#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Motivational problem: Add to a range and query for maximum

struct LazySegmentTree {
  private:
    int n;
    vector<int> tree, lazy;
    const int INF = 1e9;

    int combine(int lval, int rval){
      return max(lval, rval);
    }

    void build(vector<int> &arr, int tidx, int tl, int tr) {
      if (tl == tr){
        tree[tidx] = arr[tl];
        return;
      }
      int tm = tl + (tr - tr) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      build(arr, lchild, tl, tm);
      build(arr, rchild, tm + 1, tr);
      tree[tidx] = combine(tree[lchild], tree[rchild]);
    }

    void push(int tidx, int lchild, int rchild){
      int delta = lazy[tidx];
      tree[lchild] += delta;
      lazy[lchild] += delta;
      tree[rchild] += delta;
      lazy[rchild] += delta;
      lazy[tidx] = 0;
    }

    void range_update(int tidx, int tl, int tr, int l, int r, int val) {
      if (l > tr || tl > r){
        return;
      }
      if (l <= tl && tr <= r){
        tree[tidx] += val;
        lazy[tidx] += val;
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      push(tidx, lchild, rchild);
      range_update(lchild, tl, tm, l, min(r, tm), val);
      range_update(rchild, tm + 1, tr, max(l, tm + 1), r, val);
    }

    int range_query(int tidx, int tl, int tr, int l, int r) {
      if (l > tr || tl > r){
        return -INF;
      }
      if (l <= tl && tr <= r){
        return tree[tidx];
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      push(tidx, lchild, rchild);
      return combine(range_query(lchild, tl, tm, l, min(r, tm)),
                     range_query(rchild, tm + 1, tr, max(l, tm + 1), r));
    }

  public:
    LazySegmentTree(vector<int> &arr) : n((int)arr.size()), tree(2 * (int)arr.size() + 1), lazy(2 * (int)arr.size()) {
      build(arr, 0, 0, n - 1);
    }

    void range_update(int l, int r, int val){
      range_update(0, 0, n - 1, l, r, val);
    }

    int range_query(int l, int r){
      return range_query(0, 0, n - 1, l, r);
    }
};

/*
MIN and CNT

constexpr int INF = 1e10;

struct Node {
  int mn, cnt, lazy;
  Node() : mn(INF), cnt(0), lazy(0) {}

  Node(int x) : mn(x), cnt(1), lazy(0) {}

  Node(int x, int cnt, int lazy) : mn(x), cnt(cnt), lazy(lazy) {

  }
};

struct LazySegmentTree {
  private:
    int n;
    vector<Node> tree;

    Node combine(Node l, Node r){
      if (l.mn == r.mn){
        return Node(l.mn, l.cnt + r.cnt, 0);
      }
      if (l.mn < r.mn){
        return Node(l.mn, l.cnt, 0);
      }
      return Node(r.mn, r.cnt, 0);
    }

    void build(int tidx, int tl, int tr){
      if (tl == tr){
        tree[tidx] = Node(0);
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      build(lchild, tl, tm);
      build(rchild, tm + 1, tr);
      tree[tidx] = combine(tree[lchild], tree[rchild]);
    }

    void push(Node &root, Node &lchild, Node &rchild){
      if (root.lazy == 0){
        return;
      }
      int delta = root.lazy;
      lchild.lazy += delta;
      lchild.mn += delta;
      rchild.lazy += delta;
      rchild.mn += delta;
      root.lazy = 0;
    }

    void range_update(int tidx, int tl, int tr, int l, int r, int delta){
      if (l > tr || tl > r){
        return;
      }
      if (l <= tl && tr <= r){
        tree[tidx].mn += delta;
        tree[tidx].lazy += delta;
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      push(tree[tidx], tree[lchild], tree[rchild]);
      range_update(lchild, tl, tm, l, min(r, tm), delta);
      range_update(rchild, tm + 1, tr, max(l, tm + 1), r, delta);
      tree[tidx] = combine(tree[lchild], tree[rchild]);
    }

    Node range_query(int tidx, int tl, int tr, int l, int r){
      if (l > tr || tl > r){
        return Node();
      }
      if (l <= tl && tr <= r){
        return tree[tidx];
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      push(tree[tidx], tree[lchild], tree[rchild]);
      auto left = range_query(lchild, tl, tm, l, min(r, tm));
      auto right = range_query(rchild, tm + 1, tr, max(l, tm + 1), r);
      return combine(left, right);
    }

  public:
    LazySegmentTree(int n) : n(n), tree(2 * n + 1) {
      build(0, 0, n - 1);
    }

    void range_update(int l, int r, int x){
      range_update(0, 0, n - 1, l, r, x);
    }

    Node range_query(int l, int r){
      return range_query(0, 0, n - 1, l, r);
    }
};

*/