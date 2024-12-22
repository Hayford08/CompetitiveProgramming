#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int int64_t

template <class T>
using ordered_multiset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// X.find_by_order(k) return kth element. 0 indexed.
// X.order_of_key(k) returns count of elements strictly less than k.

template <typename T>
inline void print(const T& value) {
  std::cout << value << "\n";
}

template <typename T, typename... Args>
inline void print(const T& first, const Args&... args) {
  std::cout << first << " ";
  print(args...);
}

inline void print(const vector<int> &v) {
  for (const int &x : v) {
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
inline void solve(){
  int n;
  cin >> n;
  return;
}

#undef int
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  if (multi) {
    cin >> t;
  }
  
  while (t--) {
    solve();
  }
  return 0;
}
