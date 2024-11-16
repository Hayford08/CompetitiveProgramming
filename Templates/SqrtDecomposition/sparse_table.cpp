#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <bit>
#include <bitset>

using namespace std;

/*
Used for static arrays without updates
*/

constexpr int MAXN = 2e5 + 5;
constexpr int K =  18; // log2(MAXN);

int sp_tree[K + 1][MAXN];
int arr[MAXN];
int n;

int func(int a, int b){ // can max, min, or sum
  return a + b;
}

void build(){
  copy(arr, arr + MAXN, sp_tree[0]);
  for (int i = 1; i <= K; i++){
    int len = 1 << i;
    int prev_len = 1 << (i - 1);
    for (int j = 0; j + len <= n; j++){
      sp_tree[i][j] = func(sp_tree[i - 1][j], sp_tree[i - 1][j + prev_len]);
    }
  }
}

int query(int l, int r){ // assuming 0-indexing
  int res = 0; // default value of choice
  for (int i = K; i >= 0; i--){
    if ((1 << i) <= r - l + 1){
      res += sp_tree[i][l];
      l += (1 << i);
    }
  }
  return res;
}


// for range minimum queries --> answer queries in O(1)
int min_query(int l, int r){
  // int i = bit_width(r - l + 1) - 1;
  int i = log2(r - l + 1);
  return min(sp_tree[i][l], sp_tree[i][r - (1 << i) + 1]);
}

