#include <iostream>
#include <vector>
using namespace std;

struct Fenwick{
  int n;
  vector<int> tree;
  int cnt;
  Fenwick(int _n) : n(_n), tree(_n), cnt(0){
    
  }

  Fenwick(vector<int> &arr) : n(arr.size()), tree(arr.size()), cnt(arr.size()) {
    // 0 - based indexing
    for (int i = 0; i < n; i++){
      tree[i] += arr[i];
      int r = i | (i + 1); 
      if (r < n){
        tree[r] += arr[i];
      }
    }
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

  int count_lt(int x){
    return sum(x - 1);
  }

  int count_gt(int x){
    return cnt - sum(x);
  }
};
