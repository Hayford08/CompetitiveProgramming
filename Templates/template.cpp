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
