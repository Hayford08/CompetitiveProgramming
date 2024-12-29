#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct Comb {
  vector<long long> fact, invFact;
  long long mod;

  Comb(int n, int mod = 1e9 + 7) : fact(n + 1), invFact(n + 1), mod(mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    long long inv = pow_mod(fact[n], mod - 2);
    for (int i = n; i >= 0; i--) {
      invFact[i] = inv;
      inv = (inv * i) % mod;
    }
  }

  long long pow_mod(long long a, long long b) {
    if (b < 0) {
      return pow_mod(pow_mod(a, -b), mod - 2);
    }
    a %= mod;
    long long res = 1;
    while (b > 0) {
      if (b & 1) {
        res = (res * a) % mod;
      }
      b >>= 1;
      a = (a * a) % mod;
    }
    return res;
  }

  long long nCr(int n, int r) {
    if (r < 0 || r > n || r < 0) {
      return 0;
    }
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
  }
};
