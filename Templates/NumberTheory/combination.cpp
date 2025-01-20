#include <bits/stdc++.h>
using namespace std;

#define int int64_t
constexpr int MOD = 1e9 + 7;
inline int add(int a, int b, int mod = MOD) {
  a %= mod;
  b %= mod;
  return (((a + b) % mod) + mod) % mod;
}

inline int mul(int a, int b, int mod = MOD) {
  a %= mod;
  b %= mod;
  return (a * b) % mod;
}

inline int pow_mod(int a, int b, int mod = MOD) {
  if (b < 0) {
    return pow_mod(pow_mod(a, -b, mod), mod - 2, mod);
  }
  a %= mod;
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = (res * a) % mod;
    }
    b >>= 1;
    a = (a * a) % mod;
  }
  return res;
}

struct Comb {
  vector<int> fact, invFact;
  int mod;

  Comb(int n, int mod) : fact(n + 1), invFact(n + 1), mod(mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    int inv = pow_mod(fact[n], mod - 2, mod);
    for (int i = n; i >= 0; i--) {
      invFact[i] = inv;
      inv = (inv * i) % mod;
    }
  }

  inline int nCr(int n, int r) {
    if (r < 0 || r > n || r < 0) {
      return 0;
    }
    if (r == 0 || r == n) {
      return 1;
    }
    return mul(fact[n], mul(invFact[r], invFact[n - r], mod), mod);
  }

  inline int stars_and_bars(int stars, int slots) {
    return nCr(stars + slots - 1, slots - 1); 
  }
};


// for r small and n large
inline int nCr(int n, int r) {
  if (r < 0 || r > n || r < 0) {
    return 0;
  }
  if (r == 0 || r == n) {
    return 1;
  }
  int res = 1;
  for (int i = 0; i < r; i++) {
    res = mul(res, n - i, MOD);
    res = mul(res, pow_mod(i + 1, MOD - 2, MOD), MOD);
  }
  return res;
}
#undef int