#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 1300, MOD = 1000000009;

class ColorfulBuilding {
  int n;
  int f[N][N], g[N][N], fact[N], ifact[N];
  int binom(int n, int m) { // binomial coefficients
    if (m > n) return 0;
    return (i64)fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
  }
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
 public:
  int count(vector<string> _a, vector<string> _b, int m) {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = (i64)fact[i - 1] * i % MOD;
    ifact[1] = 1;
    for (int i = 2; i < N; ++i) ifact[i] = ((i64)MOD - MOD / i) * ifact[MOD % i] % MOD;
    ifact[0] = 1;
    for (int i = 1; i < N; ++i) ifact[i] = (i64)ifact[i - 1] * ifact[i] % MOD;
    std::string a, b;
    for (int i = 0; i < _a.size(); ++i) a += _a[i];
    for (int i = 0; i < _b.size(); ++i) b += _b[i];
    n = a.length();
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    f[n - 1][1] = g[n - 1][1] = 1;
    // f[i][j]: considering i-th element, length = j
    // g[i][j]: f[i][j] && i-th element must be the first element of the sequence
    for (int i = n - 2; i >= 0; --i) {
      for (int j = 1; j <= m; ++j) {
        add(f[i][j], f[i + 1][j] * (n - 1LL - i));
        add(g[i][j], f[i + 1][j - 1]);
      }
      for (int j = i + 1; j < n; ++j) {
        if (!(a[i] == a[j] && b[i] == b[j])) continue;
        for (int k = 1; k <= m; ++k)
          add(g[i][k], (i64)binom(n - i - 2, n - j - 1) * fact[j - i - 1] % MOD * (g[j][k] - g[j][k - 1]));
      }
      for (int j = 1; j <= m; ++j) add(f[i][j], g[i][j]);
    }
    return (f[0][m] + MOD) % MOD;
  }
};
