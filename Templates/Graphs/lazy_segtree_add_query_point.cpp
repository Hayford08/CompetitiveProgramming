#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Motivational problem: array of values but can add an amount to specific ranges

struct AdditionOnSegments{
  private:
    int n;
    vector<int> tree;

    void build(vector<int> &arr, int tidx, int tl, int tr){
      if (tl == tr){
        tree[tidx] = arr[tl];
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      build(arr, lchild, tl, tm);
      build(arr, rchild, tm + 1, tr);
      tree[tidx] = 0; // base value of root
    }

    void range_update(int tidx, int tl, int tr, int l, int r, int add) {
      if (l > tr || tl > r){
        return;
      }
      if (l <= tl && tr <= r){
        tree[tidx] += add;
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      range_update(lchild, tl, tm, l, min(r, tm), add);
      range_update(rchild, tm + 1, tr, max(tm + 1, l), r, add);
    }

    int point_query(int tidx, int tl, int tr, int pos){
      if (tl == tr){
        return tree[tidx];
      }
      int tm = tl + (tr - tl) / 2;
      if (pos <= tm){
        return point_query(tidx + 1, tl, tm, pos);
      }
      return point_query(tidx + 2 * (tm - tl + 1), tm + 1, tr, pos);
    }

  public:
    AdditionOnSegments(vector<int> &arr) : n((int)arr.size()), tree(2 * (int)arr.size() + 1) {

    }

    void range_update(int l, int r, int add){
      range_update(0, 0, n - 1, l, r, add);
    }

    int point_query(int pos){
      return point_query(0, 0, n - 1, pos);
    }
};


// Motivational problem: update a whole range with a specific value and do regular queries

struct LazySegmentTree {
  private:
    int n;
    vector<int> tree;
    vector<bool> marked;

    int combine(int lval, int rval){
      return lval + rval;
    }

    void build(vector<int> &arr, int tidx, int tl, int tr){
      if (tl == tr){
        tree[tidx] = arr[tl];
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      build(arr, lchild, tl, tm);
      build(arr, rchild, tm + 1, tr);
      tree[tidx] = combine(tree[lchild], tree[rchild]);
    }

    void push(int tidx, int lchild, int rchild){
      if (marked[tidx]){
        tree[lchild] = tree[rchild] = tree[tidx];
        marked[lchild] = marked[rchild] = true;
        marked[tidx] = false;
      }
    }

    void range_update(int tidx, int tl, int tr, int l, int r, int val) {
      if (l > tr || tl > r){
        return;
      }
      if (l <= tl && tr <= r){
        tree[tidx] = val;
        marked[tidx] = true;
        return;
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      push(tidx, lchild, rchild);
      range_update(lchild, tl, tm, l, min(tm, r), val);
      range_update(rchild, tm + 1, tr, max(tm + 1, l), r, val);
      tree[tidx] = combine(tree[lchild], tree[rchild]);
    }

    int point_query(int tidx, int tl, int tr, int pos){
      if (tl == tr){
        return tree[tidx];
      }
      int tm = tl + (tr - tl) / 2;
      int lchild = tidx + 1;
      int rchild = tidx + 2 * (tm - tl + 1);
      push(tidx, lchild, rchild);
      if (pos <= tm){
        return point_query(lchild, tl, tm, pos);
      }
      return point_query(rchild, tm + 1, tr, pos);
    }

  public:
    LazySegmentTree(vector<int> &arr) : n((int)arr.size()), tree(2 * (int)arr.size()), marked(2 * (int)arr.size(), 0) {
      build(arr, 0, 0, n - 1);
    }

    LazySegmentTree(int n) : n(n), tree(2 * n), marked(2 * n, 0) {}

    void range_update(int l, int r, int val){
      range_update(0, 0, n - 1, l, r, val);
    }

    int point_query(int pos){
      return point_query(0, 0, n - 1, pos);
    }
};