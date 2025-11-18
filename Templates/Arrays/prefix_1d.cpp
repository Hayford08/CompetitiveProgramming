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

// 1-based indexing
template <typename T>
struct Prefix {
  vector<T> pref;

  Prefix() {}

  Prefix(const vector<T> &arr) {
    int n = arr.size();
    pref.resize(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
      pref[i] = pref[i - 1] + arr[i - 1];
    }
  }

  T query(int l, int r) {
    if (l > r || r < 0) return T{};
    return pref[r] - (l > 0 ? pref[l - 1] : 0);
  }

  T query(int r) {
    if (r < 0) return T{};
    return pref[r];
  }
};


// struct Prefix {
//   vector<long long> pref;
  
//   Prefix(vector<int> &arr) {
//     int n = arr.size();
//     pref = vector<long long>(n, arr[0]);
//     for (int i = 1; i < n; i++) {
//       pref[i] = pref[i -  1] + arr[i];
//     }
//   }

//   long long query(int r) {
//     if (r < 0) return 0;
//     return pref[r];
//   }

//   long long query(int l, int r) {
//     if (l > r || r < 0) {
//       return 0;
//     }
//     return l <= 0 ? pref[r] : pref[r] - pref[l - 1];
//   }
// };
