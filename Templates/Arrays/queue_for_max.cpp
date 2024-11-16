#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <numeric>
#include <cstdio> // fflush, freopen
#include <cmath>
#include <stack>
#include <cassert>

using namespace std;
#define int long long
constexpr int INF = 1e18;
using pii = pair<int, int>;

struct Queue{
  stack<pii> stk1, stk2;

  int size(){
    return stk1.size() + stk2.size();
  }

  bool is_empty(){
    return size() == 0;
  }

  void push(int val){
    int mx = val;
    if (stk2.size()){
      mx = max(mx, stk2.top().second);
    }
    stk2.push(make_pair(val, mx));
  }

  void pop(){
    if (stk1.empty()){
      while (stk2.size()){
        int val = stk2.top().first;
        int mx = stk2.top().first;
        if (stk1.size()){
          mx = max(mx, stk1.top().second);
        }
        stk1.push(make_pair(val, mx));
        stk2.pop();
      }
    }
    assert(!stk1.empty());
    stk1.pop();
  }

  int get_max(){
    if (is_empty()){
      return -INF;
    }
    if (stk1.size() && stk2.size()){
      return max(stk1.top().second, stk2.top().second);
    }
    if (stk1.size()){
      return stk1.top().second;
    }
    return stk2.top().second;
  }
};