#include<bits/stdc++.h>
using namespace std;

struct DnC {
  int N, K;
  // needs to adapt to problem
  static constexpr long long DEFAULT = 4e18;
  vector<long long> dp, ndp, pref;
  // add other data structures as see fit and update constructor
  DnC(int n, int k, const vector<long long> &pref) : N(n), K(min(n, k)), dp(n + 1, DEFAULT), ndp(n + 1), pref(pref) {}

  // needs implementation
  long long cost(int l, int r) {
    return (pref[r] - pref[l - 1]) * (r - l + 1);
  }

  void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = l + (r - l) / 2;
    long long best = DEFAULT;
    int opt = 0;
    // mid - 1 if a segment cannot be empty else mid 
    for (int k = optl; k <= min(mid - 1, optr); k++) {
      long long curr = dp[k] + cost(k + 1, mid);
      if (curr < best) {
        best = curr;
        opt = k;
      }
    }
    ndp[mid] = best;
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
  }

  long long solve() {
    dp[0] = 0;
    for (int rem = 1; rem <= K; rem++) {
      fill(ndp.begin(), ndp.end(), DEFAULT);
      compute(1, N, 0, N - 1);
      dp.swap(ndp);
    }
    return dp[N];
  }
};