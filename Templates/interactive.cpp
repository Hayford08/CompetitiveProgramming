#include <bits/stdc++.h>
using namespace std;
#define int long long

template <typename T>
inline void print(const T& value) {
  std::cout << value << "\n";
}

bool multi = true;
constexpr int MAXN = 2e5 + 1;
int arr[MAXN];
int n;


inline void solve(){
  int l = 1, r = n;
  int ans = -1;
  while (l <= r){
    int mid = l + (r - l) / 2;
    cout << "? " << (mid - l + 1) << " ";
    for (int i = l; i <= mid; i++){
      cout << i << " ";
    }
    cout << "\n" << flush;
    int res;
    cin >> res;
    if (res > arr[mid] - arr[l - 1]){
      ans = mid;
      r = mid - 1;
    }
    else {
      l = mid + 1;
    }
  }
  cout << "! " << ans << "\n" << flush;
}

int32_t main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    arr[0] = 0;
    for (int i = 1; i <= n; i++){
      cin >> arr[i];
      arr[i] += arr[i - 1];
    }
    solve();
  }
  return 0;
}
