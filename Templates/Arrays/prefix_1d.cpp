#include <bits/stdc++.h>
using namespace std;

// template <typename T>
// class Prefix1D {
// private:
//   vector<T> prefix;
// public:
//   Prefix1D(vector<T> &arr) {
//     int n = arr.size();
//     prefix.resize(n);
//     prefix[0] = arr[0];
//     for (int i = 1; i < n; i++) {
//       prefix[i] = combine(prefix[i - 1], arr[i]);
//     }
//   }

//   T combine(T left_val, T right_val) {
//     return left_val + right_val;
//   }

//   T query(int l, int r) {
//     if (l == 0) {
//       return prefix[r];
//     }
//     return prefix[r] - prefix[l - 1];
//   }
// };


struct Prefix {
  vector<long long> pref;
  
  Prefix(vector<int> &arr) {
    int n = arr.size();
    pref = vector<long long>(n, arr[0]);
    for (int i = 1; i < n; i++) {
      pref[i] = pref[i -  1] + arr[i];
    }
  }

  long long query(int r) {
    if (r < 0) return 0;
    return pref[r];
  }

  long long query(int l, int r) {
    if (l > r || r < 0) {
      return 0;
    }
    return l <= 0 ? pref[r] : pref[r] - pref[l - 1];
  }
};
