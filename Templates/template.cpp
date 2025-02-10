#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

struct FastIO {
  FastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(10);
  }
} fast_io;

template <class T>
using ordered_multiset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// X.find_by_order(k) return kth element. 0 indexed.
// X.order_of_key(k) returns count of elements strictly less than k.

template <typename T>
inline void pout(const T& value) {
  std::cout << value << "\n";
}

template <typename T, typename... Args>
inline void pout(const T& first, const Args&... args) {
  std::cout << first << " ";
  pout(args...);
}

template <typename T>
inline void pout(const vector<T> &v) {
  for (const T &x : v) {
    cout << x << " ";
  }
  cout << "\n";
}

// For interactive problems
template <typename T>
inline void print_flush(const T& value) {
  cout << value << "\n" << flush;
}

bool multi = true;
// #define int int64_t // careful with MLE / TLE
inline void solve(){
  int n;  
  cin >> n;
  return;
}

#undef int
int main(){
  int t = 1;
  if (multi) {
    cin >> t;
  }
  
  while (t--) {
    solve();
  }
  return 0;
}
