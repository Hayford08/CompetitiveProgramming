#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

vector<vector<int>> combs;

/*
  Count the number of values in combs that have multiples 
  up to target
*/
inline int count_pie(int target){
  int res = 0;
  int n = combs.size();
  for (int i = 1; i <= n; i++){
    int sign = i & 1 ? 1 : -1;
    for (auto &x : combs[i]){
      res += sign * (target / x);
    }
  }
  return res;
}

void pie(const vector<int> &arr, long long val, int x, int idx, int cnt, long long &res){
  if (x > val){
    return;
  }
  if (idx >= arr.size()){
    if (cnt == 0){
      return;
    }
    int sign = cnt & 1 ? 1 : -1;
    res += sign * (val / x);
    return;
  }
  pie(arr, val, x, idx + 1, cnt, res);
  pie(arr, val, lcm(x, arr[idx]), idx + 1, cnt + 1, res);
}