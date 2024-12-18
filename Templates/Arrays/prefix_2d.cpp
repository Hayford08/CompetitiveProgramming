#include <bits/stdc++.h>
using namespace std;

using matrix = vector<vector<int>>;
struct Prefix2D {
  matrix pref;
  Prefix2D(const matrix &mat) {
    int n = mat.size(), m = mat[0].size();
    pref = matrix(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        pref[i + 1][j + 1] = mat[i][j] + pref[i + 1][j] + pref[i][j + 1] - pref[i][j];
      }
    }
  }

  // 1-indexed
  int query(int l1, int r1, int l2, int r2) {
    return pref[l2][r2] - pref[l1 - 1][r2] - pref[l2][r1 - 1] + pref[l1 - 1][r1 - 1];
  }
};
