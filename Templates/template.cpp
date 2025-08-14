#ifdef __cplusplus
#define _Alignof(type) __alignof__(type)
#endif
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

bool multi = true;
inline void solve(){
  int n;  
  cin >> n;
  return;
}

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
