#include <bits/stdc++.h>
using namespace std;

// NTT (Number Theoretic Transform)
constexpr int MOD = 998244353;
inline int modexp(int a, int b, int mod = MOD) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = (1LL * res * a) % mod;
    }
    a = (1LL * a * a) % mod;
    b >>= 1;
  }
  return res;
}

inline int findPrimitiveRoot(int p) {
  int phi = p - 1; // order of the multiplicative group
  vector<int> factors;
  int n = phi;
  // Factorize phi
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      factors.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }

  if (n > 1) {
    factors.push_back(n);
  }

  // Test potential primitive roots.
  for (int res = 2; res <= p; res++) {
    bool ok = true;
    for (int factor : factors) {
      if (modexp(res, phi / factor, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return res;
    }
  }
  return -1; // Should never happen if p is prime.
}


struct NTT {
  int mod, root, root_pw, inv_root;

  // Constructor with given mod, root, and root_pw.
  NTT(int mod, int root, int root_pw) : mod(mod), root(root), root_pw(root_pw) {
    inv_root = modexp(root, mod - 2, mod);
  }

  // Constructor from a prime p of the form p = c * 2^k + 1.
  NTT(int p) : mod(p) {
    int g = findPrimitiveRoot(p);
    root_pw = 1;
    int c = p - 1;
    // c is the odd part and root_pw = 2^k.
    while (c % 2 == 0) {
      c /= 2;
      root_pw <<= 1;
    }
    // Convert g to a primitive 2^k-th root of unity
    root = modexp(g, c, p);
    inv_root = modexp(root, p - 2, p);
  }

  // In-place iterative Number Theoretic Transform.
  inline void transform(vector<int> &a, bool invert) const {
    int n = a.size();
    // Bit-reversal permutation:
    for (int i = 1, j = 0; i < n; i++) {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1)
        j ^= bit;
      j ^= bit;
      if (i < j)
        swap(a[i], a[j]);
    }
    // Cooley-Tukey:
    for (int len = 2; len <= n; len <<= 1) {
      // Compute wlen = (root or inv_root)^(root_pw/len) mod mod.
      int wlen = modexp(invert ? inv_root : root, root_pw / len, mod);
      int half = len / 2;
      for (int i = 0; i < n; i += len) {
        int w = 1;
        for (int j = 0; j < half; j++) {
          int u = a[i+j];
          int v = (int)((long long)a[i + j + half] * w % mod);
          a[i + j] = u + v < mod ? u + v : u + v - mod;
          a[i + j + half] = u - v >= 0 ? u - v : u - v + mod;
          w = (int)((long long)w * wlen % mod);
        }
      }
    }
    if (invert) {
      int n_inv = modexp(n, mod - 2, mod);
      for (int &x : a)
        x = (int)((long long)x * n_inv % mod);
    }
  }

  // Multiply two polynomials modulo mod using NTT.
  inline vector<int> multiply(const vector<int> &a, const vector<int> &b) const {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    int sz = a.size() + b.size() - 1;
    while (n < sz) {
      n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    transform(fa, false);
    transform(fb, false);
    for (int i = 0; i < n; i++)
      fa[i] = (int)((long long)fa[i] * fb[i] % mod);
    transform(fa, true);

    fa.resize(a.size() + b.size() - 1);
    return fa;
  }
};
