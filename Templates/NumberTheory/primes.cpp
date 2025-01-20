#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

constexpr int MX = 5e5 + 5;
vector<int> primes;
bool is_prime[MX];

/**
 * @brief Compute the prime numbers up to, but excluding, MX.
 * 
 */
void sieve() {
  fill(is_prime, is_prime + MX, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; 1ll * i * i < MX; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      for (int j = 1ll * i * i; j < MX; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

/**
 * @brief Compute the smallest prime factor of each number from 1 to x.
 * 
 * @param x 
 * @return vector<int> 
 */
vector<int> spf(int x) {
  vector<int> res(x + 1);
  iota(res.begin(), res.end(), 0);
  for (int i = 2; i * i <= x; i++) {
    if (res[i] == i) {
      for (int j = i * i; j <= x; j += i) {
        if (res[j] == j) {
          res[j] = i;
        }
      }
    }
  }
  return res;
}

vector<int> primes;
vector<bool> marked;
void sieve(int n) {
  primes.clear();
  marked = vector<bool>(n + 1);
  for (int i = 2; i <= n; i++) {
    if (marked[i]) continue;
    primes.push_back(i);
    for (long long j = 1ll * i * i; j <= 1ll * n; j += i){
      marked[j] = true;
    }
  }
}

/*
constexpr int MAXN = 1e6 + 5;
vector<bool> marked(MAXN);
void sieve() {
  marked[0] = marked[1] = true;
  for (int i = 2; i * i < MAXN; i++) {
    if (marked[i]) continue;
    for (long long j = 1ll * i * i; j < 1ll * MAXN; j += i){
      marked[j] = true;
    }
  }
}
*/
  