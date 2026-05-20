#include <bits/stdc++.h>
#include <bit>
using namespace std;

struct SparseTable2D {
  int n, m, K1, K2;
  vector<vector<vector<int>>> st;

  int id(int x, int y) const {
    return x * m + y;
  }

  int lg(int x) const {
    return std::bit_width((unsigned)x) - 1;
  }

  int func(int a, int b) const {
    return max(a, b);
  }

  int func4(int a, int b, int c, int d) const {
    return max(max(a, b), max(c, d));
  }

  SparseTable2D(const vector<vector<int>>& a) {
    n = a.size();
    m = a[0].size();

    K1 = lg(n) + 1;
    K2 = lg(m) + 1;

    st.assign(K1, vector<vector<int>>(K2, vector<int>(n * m)));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        st[0][0][id(i, j)] = a[i][j];
      }
    }

    for (int k1 = 0; k1 < K1; k1++) {
      for (int k2 = 0; k2 < K2; k2++) {
        if (k1 == 0 && k2 == 0) continue;

        for (int i = 0; i + (1 << k1) <= n; i++) {
          for (int j = 0; j + (1 << k2) <= m; j++) {
            if (k1 > 0) {
              st[k1][k2][id(i, j)] = func(
                st[k1 - 1][k2][id(i, j)],
                st[k1 - 1][k2][id(i + (1 << (k1 - 1)), j)]
              );
            } else {
              st[k1][k2][id(i, j)] = func(
                  st[k1][k2 - 1][id(i, j)],
                  st[k1][k2 - 1][id(i, j + (1 << (k2 - 1)))]
              );
            }
          }
        }
      }
    }
  }

  int query(int x1, int y1, int x2, int y2) const {
    int k1 = lg(x2 - x1 + 1);
    int k2 = lg(y2 - y1 + 1);

    int nx = x2 - (1 << k1) + 1;
    int ny = y2 - (1 << k2) + 1;

    return func4(
      st[k1][k2][id(x1, y1)],
      st[k1][k2][id(x1, ny)],
      st[k1][k2][id(nx, y1)],
      st[k1][k2][id(nx, ny)]
    );
  }
};
