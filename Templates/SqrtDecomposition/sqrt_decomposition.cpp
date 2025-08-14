#include <bits/stdc++.h>
using namespace std;

vector<int> arr, b;
int n, s;
void build() {
  s = (int) sqrt(1.0 * n) + 1;
  b = vector<int>(s);
  for (int i = 0; i < n; i++){
    b[i / s] += arr[i];
  }
}

void query(){
  int q;
  cin >> q;
  while (q--){
    int l, r;
    cin >> l >> r;
    int sum = 0;
    int bl = l / s, br = r / s;
    if (bl == br) {
      // do something
      sum = accumulate(arr.begin() + l, arr.begin() + r + 1, 0);
      continue;
    }
    for (int i = l, end = (bl + 1) * s - 1; i <= end; i++) {
      sum += arr[i];
    }
    for (int i = bl + 1; i <= br - 1; i++) {
      sum += b[i];
    }
    for (int i = br * s; i <= r; i++) {
      sum += arr[i];
    }
  }
}

