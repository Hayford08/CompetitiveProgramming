#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Subtract two large numbers represented as strings, with the assumption that
 * the first number is greater than or equal to the second number.
 * 
 * @param a 
 * @param b 
 * @return string 
 */
inline string subtract(const string &a, const string &b) {
  int n = a.size(), m = b.size();
  string res;
  int carry = 0;
  int i = n - 1, j = m - 1;
  while (i >= 0 || j >= 0) {
    int x = (i >= 0 ? a[i] - '0' : 0);
    int y = (j >= 0 ? b[j] - '0' : 0);
    int diff = x - y - carry;
    carry = 0;
    if (diff < 0) {
      diff += 10;
      carry = 1;
    }
    res.push_back(diff + '0');
    i--;
    j--;
  }
  while (res.size() > 1 && res.back() == '0') {
    res.pop_back();
  }
  ranges::reverse(res);
  return res;
}

/**
 * @brief Converts a number represented as a string from base 10 to another base.
 * 
 * @param num 
 * @param b 
 * @return string 
 */
inline string convertBase(string num, int b) {
  if(num == "0") return "0";
  string res = "";
  while(num.size()) {
      int carry = 0;
      string quotient = "";
      for (char c : num) {
          int cur = carry * 10 + (c - '0');
          int q = cur / b;
          carry = cur % b;
          if (quotient.size() || q != 0) {
            quotient.push_back(q + '0');
          }
      }
      res.push_back(carry + '0');
      num = quotient;
  }
  ranges::reverse(res);
  return res;
}

/**
 * @brief Converts a number represented as a string from one base to another.
 * 
 * @param num 
 * @param baseFrom 
 * @param baseTo 
 * @return string 
 */
inline string convertBase(string num, int baseFrom, int baseTo) {
  if(num == "0") return "0";
  if (baseFrom == baseTo) return num;
  string res = "";
  
  auto charToValue = [](char c) -> int {
    if (isdigit(c))
      return c - '0';
    else if (isalpha(c))
      return toupper(c) - 'A' + 10;
  };

  auto valueToChar = [](int v) -> char {
    if (v < 10)
      return '0' + v;
    else
      return 'A' + (v - 10);
  };

  while(!num.empty()) {
      int carry = 0;
      string quotient = "";
      for(char c : num) {
          int cur = carry * baseFrom + charToValue(c);
          int q = cur / baseTo;
          carry = cur % baseTo;
          if(!quotient.empty() || q != 0)
              quotient.push_back(valueToChar(q));
      }
      res.push_back(valueToChar(carry));
      num = quotient;
  }
  reverse(res.begin(), res.end());
  return res;
}
