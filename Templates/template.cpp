#include <bits/stdc++.h>
using namespace std;
#define int int64_t

template <typename T>
inline void print(const T& value) {
  std::cout << value << "\n";
}

template <typename T, typename... Args>
inline void print(const T& first, const Args&... args) {
  std::cout << first << " ";
  print(args...);
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
