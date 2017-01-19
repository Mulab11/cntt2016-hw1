#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class SemiPerfectPower {
  static const int N = 500000 + 10, M = 60000 + 10;
  bool s[N], c[N]; // s[i] : whether i is square-free, c[i] : cube-free
  int tag[N]; // i's min prime factor
  int *sum[M]; // sum of s of multipliers
  void sieve() {
    static int p[N];
    static bool flag[N];
    int cnt = 0;
    s[1] = c[1] = true;
    for (int i = 2; i < N; ++i) {
      if (!flag[i]) p[++cnt] = tag[i] = i;
      for (int j = 1, k; j <= cnt && (k = i * p[j]) < N; ++j) {
        flag[k] = true;
        tag[k] = p[j];
        if (i % p[j] == 0) break;
      }
    }
    for (int i = 2; i < N; ++i) {
      s[i] = s[i / tag[i]], c[i] = c[i / tag[i]];
      if ((i / tag[i]) % tag[i] == 0) {
        s[i] = false;
        if ((i / tag[i] / tag[i]) % tag[i] == 0) c[i] = false;
      }
    }
    for (int i = 1; i < M; ++i) {
      int tot = (N - 1) / i;
      sum[i] = new int[tot + 1];
      sum[i][0] = 0;
      for (int j = 1; j <= tot; ++j) sum[i][j] = sum[i][j - 1] + s[j * i];
    }
  }
  inline i64 sqr(i64 x) { return x * x; }
  inline i64 cube(i64 x) { return x * x * x; }
  i64 llsqrt(i64 x) { // square root
    i64 res = sqrt(x) - .5;
    if (res < 0) res = 0;
    while (sqr(res + 1) <= x) ++res;
    return res;
  }
  i64 llcbrt(i64 x) { // cubic root
    i64 res = cbrt(x) - .5;
    if (res < 0) res = 0;
    while (cube(res + 1) <= x) ++res;
    return res;
  }
  i64 gcd(i64 a, i64 b) { return b ? gcd(b, a % b) : a; }
  i64 solve(i64 n) {
    // the full algorithm is complicated
    i64 res = 0;
    for (int i = 1; cube(i) < n; ++i) if (s[i]) res += llsqrt(n / i) - i;
    for (int i = 1; sqr(sqr(i)) < n; ++i) {
      if (!c[i]) continue;
      for (int k = 1; cube(k) <= i; ++k) {
        int j = i / gcd(sqr(k), i), t = (i64)sqr(k) / gcd(sqr(k), i);
        if (!s[j]) continue;
        int r = llcbrt(n / i);
        static int p[N];
        int tot = 0;
        for (int x = j; x > 1; x /= tag[x]) p[tot++] = tag[x];
        for (int s = 0; s < (1 << tot); ++s) {
          int c = 1, d = 1;
          for (int x = 0; x < tot; ++x) if (s >> x & 1) d *= p[x], c = -c;
          res += c * (sum[d][r / t / d] - sum[d][i / t / d]);
        }
      }
    }
    return res;
  }
 public:
  SemiPerfectPower() { sieve(); }
  i64 count(i64 l, i64 r) { return solve(r) - solve(l - 1); }
};
