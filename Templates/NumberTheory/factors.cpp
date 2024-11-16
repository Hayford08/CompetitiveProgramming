#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

constexpr int MX = 5e4 + 5;
vector<vector<int>> factors(MX);

void find_factors() {
  for(int i = 1; i < MX; i++) {
    for (int j = 1; j * j <= i; j++) {
      if (i % j == 0) {
        factors[i].push_back(j);
        int other = i / j;
        if (other != j) {
          factors[i].push_back(other);
        }
      }
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
