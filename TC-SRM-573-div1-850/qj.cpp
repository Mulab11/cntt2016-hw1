#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class WolfPack {
  static const int N = 1000000 + 10, MOD = 1000000007;
  int fact[N], ifact[N];
  int binom(int n, int m) { // binomial coefficients
    if (m > n) return 0;
    return (i64)fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
  }
  int solve(const std::vector<int> &p, int m) {
    // just solve the 1-d case
    int l = *std::min_element(p.begin(), p.end()) - m, r = *std::max_element(p.begin(), p.end()) + m;
    int res = 0;
    for (int i = l; i <= r; ++i) {
      int cur = 1;
      for (int j = 0; j < p.size(); ++j) {
        int x = m, y = abs(p[j] - i);
        if (y > x || (x - y) & 1) {
          cur = 0;
          break;
        }
        int z = (x - y) / 2;
        cur = (i64)cur * binom(m, y + z) % MOD;
      }
      (res += cur) %= MOD;
    }
    return (res + MOD) % MOD;
  }
 public:
  int calc(vector<int> x, vector<int> y, int m) {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = (i64)fact[i - 1] * i % MOD;
    ifact[0] = ifact[1] = 1;
    for (int i = 2; i < N; ++i) ifact[i] = ((i64)MOD - MOD / i) * ifact[MOD % i] % MOD;
    for (int i = 1; i < N; ++i) ifact[i] = (i64)ifact[i - 1] * ifact[i] % MOD;
    const int n = x.size();
    for (int i = 0; i < n; ++i) {
      // just rotate the coordinate
      // then x and y become independent
      int a = x[i], b = y[i];
      x[i] = a + b, y[i] = a - b;
    }
    return (i64)solve(x, m) * solve(y, m) % MOD;
  }
};
