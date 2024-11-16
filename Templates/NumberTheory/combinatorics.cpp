#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

long long nCr(long long n, long long r){
    if (r == 0 || r == n)
        return 1;
    if (r > n) {
        return 0;
    }
    r = min(r, n - r);
    long long res = 1;
    for (int i = 0; i < r; i++){
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

const long long MOD = 1e9 + 7;
vector<long long> fact, inv_fact;

inline long long pow_mod(long long a, long long b) {
    long long res = 1;
    while (b > 0){
        if (b & 1){
            res = (res * a) % MOD;
        }
        b >>= 1;
        a = (a * a) % MOD;
    }
    return res;
}

inline void compute_factorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; i++){
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    long long inv = pow_mod(fact.back(), MOD - 2);
    for (int i = n; i >= 1; i--){
        inv_fact[i] = inv;
        inv = (inv * i) % MOD;
    }
}

inline long long nCr(int n, int r) {
    if (r < 0 || r > n){
        return 0;
    }
    long long res = fact[n];
    res = (res * inv_fact[r]) % MOD;
    res = (res * inv_fact[n - r]) % MOD;
    return res;
}


