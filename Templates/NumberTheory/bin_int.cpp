#include<iostream>
using namespace std;

#define int int64_t
string bin(int n) {
  string s = "";
  while (n != 0) {
    s += (n % 2) + '0';
    n /= 2;
  }
  reverse(s.begin(), s.end());
  return s;
}

int to_int(string s) {
  int n = 0;
  for(char c : s) {
    n = 2 * n + (c - '0');
  }
  return n;
}
#undef int