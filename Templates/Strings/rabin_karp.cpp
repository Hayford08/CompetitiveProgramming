#include <iostream>
#include <vector>
using namespace std;
constexpr long long MOD1 = 1e9 + 7;
constexpr long long MOD2 = 1e9 + 9;

long long pow_mod(long long a, long long b, long long mod){
  long long ans = 1;
  a %= mod;
  while (b) {
    if (b & 1){
      ans = (ans * a) % mod;
    }
    b >>= 1;
    a = (a * a) % mod;
  }
  return ans;
}

struct RabinKarp {
  int P1, P2;
  long long MOD1, MOD2;
  vector<long long> pref1, pref2, inv_pows1, inv_pows2;

  RabinKarp(const string &s, int p1 = 53, int p2 = 911, long long mod1 = 1e9+7, long long mod2 = 1e9+9) {
    P1 = p1;
    P2 = p2;
    MOD1 = mod1;
    MOD2 = mod2;
    int n = s.size();
    pref1 = vector<long long>(n + 1);
    pref2 = vector<long long>(n + 1);
    inv_pows1 = vector<long long>(n + 1);
    inv_pows2 = vector<long long>(n + 1);

    long long h1 = 0, h2 = 0;
    long long pwr1 = 1, pwr2 = 1;
    for (int i = 1; i <= n; i++){
      int x = s[i - 1] - 'a' + 1;
      h1 = (h1 + pwr1 * x) % MOD1;
      pref1[i] = h1;
      pwr1 = (pwr1 * P1) % MOD1;
    }

    for (int i = 1; i <= n; i++) {
      int x = s[i - 1] - 'a' + 1;
      h2 = (h2 + pwr2 * x) % MOD2;
      pref2[i] = h2;
      pwr2 = (pwr2 * P2) % MOD2;
    }

    pwr1 = pow_mod(pwr1, MOD1 - 2, MOD1);
    for (int i = n; i >= 0; i--){
      inv_pows1[i] = pwr1;
      pwr1 = (pwr1 * P1) % MOD1;
    }

    pwr2 = pow_mod(pwr2, MOD2 - 2, MOD2);
    for (int i = n; i >= 0; i--){
      inv_pows2[i] = pwr2;
      pwr2 = (pwr2 * P2) % MOD2;
    }
  }

  pair<long long, long long> query(int l, int r) {
    long long hash1 = (((pref1[r + 1] - pref1[l] + MOD1) % MOD1) * inv_pows1[l]) % MOD1;
    long long hash2 = (((pref2[r + 1] - pref2[l] + MOD2) % MOD2) * inv_pows2[l]) % MOD2;
    return {hash1, hash2};
  }
};

