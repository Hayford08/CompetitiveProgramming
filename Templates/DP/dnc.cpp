#include<bits/stdc++.h>
using namespace std;

struct DnC {
  int N, K;
  using Cost = long long(*)(int, int);
  Cost cost;
  static constexpr long long INF = 4e18;
  vector<long long> dp, ndp;

  DnC() {}

  DnC(int n, int k, Cost cost) : N(n), K(min(n, k)), cost(cost), dp(n + 1, INF), ndp(n + 1, INF) {}

  void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = l + (r - l) / 2;
    long long best = INF;
    int opt = optl;

    // mid - 1 for non empty subarrays
    for (int k = optl, end = min(mid - 1, optr); k <= end; k++) {
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
      fill(ndp.begin(), ndp.end(), INF);
      compute(1, N, 0, N - 1);
      dp.swap(ndp);
    }
    return dp[N];
  }
};