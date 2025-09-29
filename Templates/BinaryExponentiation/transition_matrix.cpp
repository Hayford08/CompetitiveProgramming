#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<int>>;
using Vector = vector<int>;
const long long MOD = 1e9 + 7;

inline Matrix mul(const Matrix& A, const Matrix& B) {
  int rows = A.size(), cols = B[0].size();
  int inner = B.size();
  Matrix result(rows, Vector(cols, 0));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      for (int k = 0; k < inner; ++k) {
        if (A[i][k] == 0 || B[k][j] == 0) continue;
        long long tmp = result[i][j] + 1ll * A[i][k] * B[k][j];
        if (tmp > MOD) {
            tmp %= MOD;
        }
        result[i][j] = tmp;
      }
    }
  }
  return result;
}

inline Matrix pow(Matrix T, int b) {
  int n = T.size();
  Matrix result(n, Vector(n, 0));
  
  for (int i = 0; i < n; ++i) result[i][i] = 1;

  while (b > 0) {
    if (b % 2 == 1) {
      result = mul(result, T);
    }
    T = mul(T, T);
    b >>= 1;
  }
  return result;
}

inline Vector apply_transitions(const Matrix& T, const Vector& V, int t) {
  Matrix m = {V};
  return mul(m, pow(T, t))[0];
}
