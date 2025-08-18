#include <bits/stdc++.h>
using namespace std;

struct Fraction {
  int num, denom;

  Fraction(int a, int b) {
    int g = gcd(a, b);
    num = a / g;
    denom = b / g;
    if (denom < 0) {
        denom *= -1;
        num *= -1;
    }
  }

  Fraction operator+(const Fraction &other) const {
    int top = num * other.denom + other.num * denom;
    int bottom = denom * other.denom;
    return Fraction(top, bottom);
  }

  Fraction operator-(const Fraction &other) const {
    int top = num * other.denom - other.num * denom;
    int bottom = denom * other.denom;
    return Fraction(top, bottom);
  }

  Fraction operator*(const Fraction &other) const {
    int top = num * other.num;
    int bottom = denom * other.denom;
    return Fraction(top, bottom);
  }

  Fraction operator/(const Fraction &other) const {
    int top = num * other.denom;
    int bottom = denom * other.num;
    return Fraction(top, bottom);
  }

  bool operator==(const Fraction &other) const {
    return num == other.num && denom == other.denom;
  }
};