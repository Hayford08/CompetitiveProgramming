#include <iostream>
#include <vector>

using namespace std;

constexpr long long MOD = 1e9 + 7;
struct RollingHash{
  using ull = unsigned long long;
  ull p;
  vector<ull> hashes;
  vector<ull> pows;

  RollingHash(const string &s, ull _p = 911) : p(_p) {
    int n = s.size();
    pows.resize(n + 1);
    hashes.resize(n + 1);

    pows[0] = 1;
    for (int i = 1; i <= n; i++){
      pows[i] = pows[i - 1] * p;
    }

    hashes[0] = 0;
    for (int i = 1; i <= n; i++){
      hashes[i] = hashes[i - 1] * p + s[i - 1];
    }
  }

  ull get_hash(int l, int r) {
    return hashes[r + 1] - hashes[l] * pows[r - l + 1];
  }

  ull get_hash(){
    return hashes.back();
  }
};