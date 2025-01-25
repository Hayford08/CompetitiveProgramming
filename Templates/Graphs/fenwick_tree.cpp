#include <iostream>
#include <vector>
using namespace std;

struct Fenwick{
  int n, cnt, mask;
  vector<int> tree;
  Fenwick(int _n) : n(_n), cnt(0), mask(1), tree(_n) {
    while (mask < n) mask <<= 1;
  }

  Fenwick(vector<int> &arr) : n(arr.size()), cnt(arr.size()), mask(1),  tree(arr.size()) {
    // 0 - based indexing
    for (int i = 0; i < n; i++){
      tree[i] += arr[i];
      int r = i | (i + 1); 
      if (r < n){
        tree[r] += arr[i];
      }
    }
    while (mask < n) mask <<= 1;
  }

  int sum(int r) {
    int res = 0;
    while (r >= 0){
      res += tree[r];
      r = (r & (r + 1)) - 1;
    }
    return res;
  }

  int sum(int l, int r){
    return sum(r) - sum(l - 1);
  }

  void add(int idx, int delta){
    cnt += delta;
    while (idx < n) {
      tree[idx] += delta;
      idx |= (idx + 1);
    }
  }

  void range_add(int l, int r, int delta) {
    if (l > r) return;
    add(l, delta);
    add(r + 1, -delta);
  }

  int count_lt(int x){
    return sum(x - 1);
  }

  int count_gt(int x){
    return cnt - sum(x);
  }

  int lower_bound(int x) {
    int idx = -1, bit = mask;
    int sum = 0;
    while (bit > 0) {
      int nidx = idx + bit;
      if (nidx < n && sum + tree[nidx] < x) {
        sum += tree[nidx];
        idx = nidx;
      }
      bit >>= 1;
    }
    return idx + 1;
  }
};
