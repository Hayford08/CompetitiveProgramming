#include <iostream>
#include <array>

using namespace std;

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

array<int, 3> xgcd_rec(int a, int b){
  if (b == 0){
    return {a, 1, 0};
  }
  auto [g, x1, y1] = xgcd_rec(b, a % b);
  return {g, y1, x1 - (a / b) * y1};
}

