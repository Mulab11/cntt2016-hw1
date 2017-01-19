#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class PenguinEmperor {
  static const int N = 350 + 10, MOD = 1000000007;
  int n;
  void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
  void comp(int a[], const int b[]) {
    // function composition
    static int res[N];
    memset(res, 0, sizeof res);
    for (int j = 0; j < n; ++j)
      if (b[j])
        for (int i = 0; i < n; ++i)
          add(res[(i + j) % n], (i64)a[i] * b[j]);
    memcpy(a, res, sizeof res);
  }
  void power(int base[], i64 exp) {
    static int res[N];
    memset(res, 0, sizeof res);
    res[0] = 1;
    for (; exp; exp >>= 1) {
      if (exp & 1) comp(res, base);
      comp(base, base);
    }
    memcpy(base, res, sizeof res);
  }
  int f[N], g[N];
 public:
  int countJourneys(int _n, i64 m) {
    n = _n;
    memset(f, 0, sizeof f);
    i64 p = m / n;
    int q = m % n;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
      memset(g, 0, sizeof g);
      g[i] = g[(n - i) % n] = 1;
      comp(f, g);
    }
    power(f, p); // giant step
    for (int i = 1; i <= q; ++i) {
      memset(g, 0, sizeof g);
      g[i] = g[(n - i) % n] = 1;
      comp(f, g); // little step
    }
    return f[0];
  }
};
