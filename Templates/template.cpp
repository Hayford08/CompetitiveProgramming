#include <bits/stdc++.h>
using namespace std;

struct FastIO {
  FastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(15);
  }
} fast_io;

namespace cp {
  template <typename T>
  void print(const T &value) {
    cout << value << "\n";
  }

  template <typename T, typename... Args>
  void print(const T &first, const Args &... args) {
    cout << first << " ";
    print(args...);
  }

  template <typename T>
  void print(const vector<T> &v) {
    for (const T &x : v)
      cout << x << " ";
    cout << "\n";
  }
}

bool multi = true;
#define int int64_t // careful with MLE / TLE
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
