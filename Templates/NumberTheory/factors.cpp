#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

constexpr int MX = 5e4 + 5;
vector<vector<int>> factors(MX);

void find_factors() {
  for (int i = 1; i < MX; i++) {
    for (int m = i; m < MX; m += i) {
      factors[m].push_back(i);
    }
  }
}

vector<int> count_multiples(const vector<int> &nums) {
  vector<int> mp(MX);
  for (int x : nums) {
    for (int f : factors[x]) {
      mp[f]++;
    }
  }
  vector<int> cnt(MX);
  for (int i = 1; i < MX; i++) {
    if (mp[i] == 0) {
      continue;
    }
    for (int j = i; j < MX; j += i) {
      cnt[j] += mp[i];
    }
  }
  return cnt;
}

constexpr int MOD = 1e9 + 7;
constexpr int INV_MOD2 = 500000004;
int sum_of_divisors_from_1_to_n(int n) {

  auto range_sum = [&](int a, int b) -> int {
    auto sum = [&](int x) -> int {
      x %= MOD;
      int res = (x * (x + 1)) % MOD;
      return (res * INV_MOD2) % MOD;
    };
    return (sum(b) - sum(a - 1) + MOD) % MOD;
  };

  int ans = 0;
  int i = 1;
  while (i <= n){
    int q = n / i;
    int nxt = n / q;
    ans = (ans + (range_sum(i, min(n, nxt)) * q) % MOD) % MOD;
    i = nxt + 1;
  }
  return ans;
} 
