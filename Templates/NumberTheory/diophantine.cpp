#include <iostream>
using namespace std;

#define int long long


int xgcd(int a, int b, int &x, int &y){
  x = 1, y = 0;
  int x1 = 0, y1 = 1;
  while (b){
    int q = a / b, r = a % b;
    tie(x, x1) = make_pair(x1, x - q * x1);
    tie(y, y1) = make_pair(y1, y - q * y1);
    a = b;
    b = r;
  }
  return a;
}

bool find_solution(int a, int b, int c, int &x, int &y, int &g){
  g = xgcd(abs(a), abs(b), x, y);
  if (c % g != 0){
    return false;
  }
  x *= c / g;
  y *= c / g;

  if (a < 0) x = -x;
  if (b < 0) y = -y;
  return true;
}

void shift(int &x, int &y, int a, int b, int k){
  x += k * b;
  y -= k * a;
}

int count_solutions(int a, int b, int c, int mnx, int mxx, int mny, int mxy){
  int x, y, g;
  if (!find_solution(a, b, c, x, y, g)){
    return 0;
  }

  a /= g;
  b /= g;

  int sign_a = a > 0 ? +1 : -1;
  int sign_b = b > 0 ? +1 : -1;

  // (mnx - x) / b <= k
  shift(x, y, a, b, (mnx - x) / b);
  if (x < mnx)
    shift(x, y, a, b, sign_b);
  if (x > mxx){
    return 0;
  }
  int lx1 = x;

  // k <= (mxx - x) / b
  shift(x, y, a, b, (mxx - x) / b);
  if (x > mxx)
    shift(x, y, a, b, -sign_b);
  int rx1 = x;

  // (y - mny) / a <= k
  shift(x, y, a, b, (y - mny) / a);
  if (y < mny)
    shift(x, y, a, b, -sign_a);
  if (y > mxy){
    return 0;
  }
  int lx2 = x;

  // k <= (y - mxy) / a
  shift(x, y, a, b, (y - mxy) / a);
  if (y > mxy)
    shift(x, y, a, b, sign_a);
  int rx2 = x;

  if (lx2 > rx2){
    swap(lx2, rx2);
  }

  int lx = max(lx1, lx2);
  int rx = min(rx1, rx2);

  if (lx > rx){
    return 0;
  }
  return 1 + (rx - lx) / abs(b);
}