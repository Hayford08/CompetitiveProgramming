#include <bits/stdc++.h>
using namespace std;

#define int int64_t
struct Comb {
  vector<int> fact, invFact;
  int mod;

  Comb(int n, int mod) : fact(n + 1), invFact(n + 1), mod(mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    int inv = pow_mod(fact[n], mod - 2);
    for (int i = n; i >= 0; i--) {
      invFact[i] = inv;
      inv = (inv * i) % mod;
    }
  }

  inline int pow_mod(int a, int b) {
    if (b < 0) {
      return pow_mod(pow_mod(a, -b), mod - 2);
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

  inline int nCr(int n, int r) {
    if (r < 0 || r > n || r < 0) {
      return 0;
    }
    if (r == 0 || r == n) {
      return 1;
    }
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
  }

  inline int add(int a, int b) {
    a %= mod;
    b %= mod;
    return (((a + b) % mod) + mod) % mod;
  }

  inline int mul(int a, int b) {
    a %= mod;
    b %= mod;
    return (a * b) % mod;
  }

  inline int stars_and_bars(int stars, int slots) {
    return nCr(stars + slots - 1, slots - 1); 
  }
};
#undef int