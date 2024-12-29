#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n = 20;
int limit = 1 << n;

int get_distance(int i, int j) {
  return 0;
}

auto tsp = [&]() -> int {
  vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        dist[i][j] = get_distance(i, j);
      }
    }
    int limit = 1 << n;
    vector<vector<int>> dp(n, vector<int>(limit, INF));
    for (int i = 0; i < n; i++) {
      dp[i][1 << i] = 1;
    }

    for (int mask = 1; mask < limit; mask++) {
      for (int pv = 0; pv < n; pv++) {
        if (dp[pv][mask] == INF) continue;
        for (int nxt = 0; nxt < n; nxt++) {
          if (mask & (1 << nxt)) continue;
          int nmask = mask | (1 << nxt);
          dp[nxt][nmask] = min(dp[nxt][nmask], dp[pv][mask] + dist[pv][nxt]);
        }
      }
    }
    int res = INF;
    for (int i = 0; i < n; i++) {
      res = min(res, dp[i][limit - 1]);
    }
    return res;
};