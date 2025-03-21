#include <bits/stdc++.h>
using namespace std;

#define int long long

// ax^2 + bx + c = 0
// Returns the smallest positive integer x that satisfies the equation
// If there is no such x, returns -1
inline int quadratic(int a, int b, int c, int MX = 6e8) {
  int l = 0, r = MX;
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (a * mid * mid + b * mid + c < 0) {
      l = mid + 1;
    }
    else {
      r = mid;
    }
  }
  if (a * l * l + b * l + c == 0) {
    return l;
  }
  return -1;
}