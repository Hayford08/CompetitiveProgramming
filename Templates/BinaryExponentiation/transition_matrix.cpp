#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<int>>;
using Vector = vector<int>;
const long long MOD = 1e9 + 7;

using Matrix = vector<vector<int>>;
using Vector = vector<int>;
const long long MOD = 1e9 + 7;

inline void mulInPlace(const Matrix &A, const Matrix &B, Matrix &C) {
  for (auto &v : C) {
    ranges::fill(v, 0);
  }
  int rows = A.size(), cols = B[0].size();
  int inner = B.size();
  for (int i = 0; i < rows; i++) {
    const auto &Ai = A[i];
    auto &Ci = C[i];
    for (int k = 0; k < inner; k++) {
      int Aik = Ai[k];
      if (Aik == 0) continue;
      const auto &Bk = B[k];
      for (int j = 0; j < cols; j++) {
        long long tmp = Ci[j] + 1ll * Aik * Bk[j];
        if (tmp > MOD) {
          tmp %= MOD;
        }
        Ci[j] = tmp;
      }
    }
  }
}

inline Matrix mul(const Matrix& A, const Matrix& B) {
  int rows = A.size(), cols = B[0].size();
  Matrix result(rows, Vector(cols, 0));
  mulInPlace(A, B, result);
  return result;
}

// Assumes T is n x n
inline Matrix pow(Matrix T, int b) {
  int n = T.size();
  Matrix result(n, Vector(n, 0));
  Matrix tmp = result;
  for (int i = 0; i < n; ++i) result[i][i] = 1;

  while (b > 0) {
    if (b % 2 == 1) {
      mulInPlace(result, T, tmp);
      result.swap(tmp);
    }
    mulInPlace(T, T, tmp);
    T.swap(tmp);
    b >>= 1;
  }
  return result;
}

inline Vector apply_transitions(const Matrix& T, const Vector& V, int t) {
  Matrix m = {V};
  return mul(m, pow(T, t))[0];
}
