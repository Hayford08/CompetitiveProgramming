#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<uint64_t>;

/*

vector<int> bitwiseMatMul(const vector<int> &X, const vector<int> &Y, int B) {
  vector<int> Z(B, 0);
  for (int col = 0; col < B; col++) {
    int colMask = 0;
    for (int row = 0; row < B; row++) {
      if ((Y[row] >> col) & 1) {
        colMask |= (1 << row);
      }
    }
    for (int row = 0; row < B; row++) {
      if (X[row] & colMask) {
        Z[row] |= (1 << col);
      }
    }
  }
  return Z;
}

*/

Matrix mul(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix result(n, 0);
  for (int j = 0; j < n; j++) {
    uint64_t aj = A[j];
    while (aj > 0) {
      int lsb = __builtin_ctzll(aj);
      result[j] |= B[lsb];
      aj &= aj - 1;
    }
  }
  return result;
}

Matrix pow(Matrix M, int b, int n) {
  Matrix result(n, 0);
  for (int i = 0; i < n; i++) {
    result[i] = 1LL << i;
  }
  while (b > 0) {
    if (b % 2 == 1) {
      result = mul(result, M);
    }
    M = mul(M, M);
    b >>= 1;
  }
  return result;
}

