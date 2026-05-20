#include <bits/stdc++.h>
using namespace std;

// using min as func but can be changed to max, gcd but not sum, xor
struct SparseTable2D {
  constexpr static int K1 = 8; // log2(200) + 1
  constexpr static int K2 = 8;
  vector<vector<int>> st[K1 + 1][K2 + 1];

  SparseTable2D(const vector<vector<int>> &mat) {
    int n = mat.size();
    int m = mat[0].size();
    for (int l1 = 0; l1 <= K1; l1++) {
      for (int l2 = 0; l2 <= K2; l2++) {
        st[l1][l2] = vector<vector<int>>(n, vector<int>(m));
      }
    }

    st[0][0] = mat;
    for (int l1 = 1; l1 <= K1; l1++) {
      int pLen = 1 << (l1 - 1);
      for (int i = 0; i + (1 << l1) <= n; i++) {
        for (int j = 0; j < m; j++) {
          st[l1][0][i][j] = func(st[l1 - 1][0][i][j], st[l1 - 1][0][i + pLen][j]);
        }
      }
    }
    for (int l2 = 1; l2 <= K2; l2++) {
      int pLen = 1 << (l2 - 1);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j + (1 << l2) <= m; j++) {
          st[0][l2][i][j] = func(st[0][l2 - 1][i][j], st[0][l2 - 1][i][j + pLen]);
        }
      }
    }
    for (int l1 = 1; l1 <= K1; l1++) {
      int p1Len = 1 << (l1 - 1);
      for (int l2 = 1; l2 <= K2; l2++) {
        int p2Len = 1 << (l2 - 1);
        for (int i = 0; i + (1 << l1) <= n; i++) {
          for (int j = 0; j + (1 << l2) <= m; j++) {
            st[l1][l2][i][j] = func(st[l1 - 1][l2 - 1][i][j], st[l1 - 1][l2 - 1][i][j + p2Len], 
                              st[l1 - 1][l2 - 1][i + p1Len][j], st[l1 - 1][l2 - 1][i + p1Len][j + p2Len]);
          }
        }
      }
    }
  }

  int query(int x1, int y1, int x2, int y2) {
    int l1 = log2(x2 - x1 + 1);
    int l2 = log2(y2 - y1 + 1);
    return func(st[l1][l2][x1][y1], st[l1][l2][x1][y2 - (1 << l2) + 1], 
                st[l1][l2][x2 - (1 << l1) + 1][y1], st[l1][l2][x2 - (1 << l1) + 1][y2 - (1 << l2) + 1]);
  }

private:
  int log2(int x) {
    return std::bit_width((unsigned long)x) - 1;
  }

  int func(int x, int y) {
    return min(x, y);
  }
  
  int func(int a, int b, int c, int d) {
    return min({a, b, c, d});
  }
};
