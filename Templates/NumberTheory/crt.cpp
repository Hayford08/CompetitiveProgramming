#include <iostream>
#include <array>
#include <vector>
using namespace std;

#define int long long

array<int, 3> xgcd(int a, int b){
  int x = 1, y = 0;
  int x1 = 0, y1 = 1;

  while (b){
    int q = a / b, r = a % b;
    tie(x, x1) = make_pair(x1, x - q * x1);
    tie(y, y1) = make_pair(y1, y - q * y1);
    a = b;
    b = r;
  }
  return {a, x, y};
}

int mod_inv(int a, int m){
  auto [g, x, _] = xgcd(a, m);
  if (g != 1){
    return -1;
  }
  return (x % m + m) % m;
}

// congruence has a, m

int crt(vector<pair<int, int>> &congruences) {
  int M = 1;
  for (auto const &[_, m] : congruences){
    M *= m;
  }
  int ans = 0;
  for (auto const &[ai, m] : congruences){
    int mi = M / m;
    int ni = mod_inv(ai, mi);
    // no solution exists
    if (ni == -1){
      return -1;
    }
    ans = (ans + (ai * mi) % M * ni) % M;
  }
  return ans;
}
