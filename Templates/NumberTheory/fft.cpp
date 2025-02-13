#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

// Fast Fourier Transform
inline void fft(vector<cd> &a, bool invert) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) { 
      j ^= bit;
    }
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * (PI / len) * (invert ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      cd w(1);
      int m = len >> 1;
      for (int j = 0; j < m; j++) {
        cd u = a[i + j], v = a[i + j + m] * w;
        a[i + j] = u + v;
        a[i + j + m] = u - v;
        w *= wlen;
      }
    }
  }

  if (invert) {
    for (cd &x : a) {
      x /= n;
    }
  }
}

// convolution of two polynomials
inline vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1, sz = a.size() + b.size();
  while (n < sz) n <<= 1;
  fa.resize(n); fb.resize(n);

  // evaluate polynomial
  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++) {
    fa[i] *= fb[i];
  }
  // interpolate polynomial
  fft(fa, true);
  vector<int> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = round(fa[i].real());
  }
  return res;
}
