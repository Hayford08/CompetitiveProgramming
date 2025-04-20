#include <bits/stdc++.h>
using namespace std;

// Inspired by https://leetcode.com/problems/find-x-value-of-array-ii/description/

int K;

struct Node {
  int val;
  array<int, 5> counts;

  Node() : val(1), counts({}) {}

  Node(int x) : val(x % K), counts({}) {
    counts[val]++;
  }

  inline Node operator+(const Node& other) const {
    Node res((val * other.val) % K);
    res.counts = counts;
    for (int i = 0; i < K; i++) {
      res.counts[(i * val) % K] += other.counts[i];
    }
    return res;
  }
};

struct SegTree {
  int n;
  vector<Node> tree;
  vector<int> arr;

  inline void build(int tIdx, int l, int r) {
    if (l == r) {
      tree[tIdx] = Node(arr[l]);
      return;
    }
    int m = l + (r - l) / 2;
    int lc = tIdx + 1;
    int rc = tIdx + 2 * (m - l + 1);
    build(lc, l, m);
    build(rc, m + 1, r);
    tree[tIdx] = tree[lc] + tree[rc];
  }

  inline void point_update(int idx, int val, int tIdx, int tl, int tr) {
    if (tl == tr) {
      arr[idx] = val;
      tree[tIdx] = Node(val);
      return;
    }
    int mid = (tl + tr) / 2;
    int lchild = tIdx + 1;
    int rchild = tIdx + 2 * (mid - tl + 1);
    if (idx <= mid) {
      point_update(idx, val, lchild, tl, mid);
    } else {
      point_update(idx, val, rchild, mid + 1, tr);
    }
    tree[tIdx] = tree[lchild] + tree[rchild];
  }

  inline Node range_query(int l, int r, int tIdx, int tl, int tr) {
    if (l > tr || r < tl) {
      return Node();
    }
    if (l <= tl && tr <= r) {
      return tree[tIdx];
    }
    int tm = (tl + tr) / 2;
    int lchild = tIdx + 1;
    int rchild = tIdx + 2 * (tm - tl + 1);
    return range_query(l, min(r, tm), lchild, tl, tm) +
           range_query(max(l, tm + 1), r, rchild, tm + 1, tr);
  }

  SegTree(int n) : n(n), tree(2 * n + 1) {}

  SegTree(const vector<int> &arr) : n(n),  tree(2 * n + 1), arr(arr) {
    build(0, 0, n - 1);
  }

  inline void point_update(int idx, int val) {
    point_update(idx, val, 0, 0, n - 1);
  }

  inline Node range_query(int l, int r) {
    return range_query(l, r, 0, 0, n - 1);
  }
};