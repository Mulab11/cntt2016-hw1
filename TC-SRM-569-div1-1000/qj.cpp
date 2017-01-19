#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class MegaFactorial {
  static const int MOD = 1000000009;
  static const int N = 20;
  int mod;
  int inv(int x) { return x == 1 ? 1 : (((i64)MOD - MOD / x) * inv(MOD % x) % MOD); } // modular inversion
  void mul(int lhs[][N], const int rhs[][N]) { // matrix multiplication
    static int res[N][N];
    memset(res, 0, sizeof res);
    for (int i = 0; i < N; ++i)
      for (int k = 0; k < N; ++k)
        for (int j = 0; j < N; ++j)
          res[i][j] = (res[i][j] + (i64)lhs[i][k] * rhs[k][j]) % mod;
    memcpy(lhs, res, sizeof res);
  }
  int solve(int n, int k, int b) {
    n += k;
    static int p[2 * N][N][N], q[2 * N][N][N];
    // p[i] : mat(p^i)
    // q[i] : mat(1) * mat(2) * ... * mat(p^i - 1)
    int cnt = 0;
    for (int t = n; t; t /= b) ++cnt;
    for (int i = 0; i < cnt; ++i) {
      memset(p[i], 0, sizeof p[i]);
      for (int j = 1; j <= k; ++j) p[i][j - 1][j] = p[i][j][j] = 1;
      p[i][N - 1][0] = i;
      p[i][N - 1][N - 1] = 1;
      if (i) {
        memcpy(q[i], q[i - 1], sizeof q[i]);
        for (int j = b - 1; j--;) mul(q[i], p[i - 1]), mul(q[i], q[i - 1]);
      } else {
        memset(q[i], 0, sizeof q[i]);
        for (int j = 0; j < N; ++j) q[i][j][j] = 1;
      }
    }
    static int res[N][N];
    memset(res, 0, sizeof res);
    for (int i = 0; i < N; ++i) res[i][i] = 1;
    static i64 mem[2 * N];
    mem[0] = 1;
    for (int i = 1; i < 2 * N; ++i) mem[i] = (i64)b * mem[i - 1];
    while (n) {
      int i = 0;
      while (mem[i + 1] <= n) ++i;
      mul(res, q[i]);
      mul(res, p[i]);
      n -= mem[i];
    }
    return res[N - 1][k];
  }
 public:
  int countTrailingZeros(int n, int k, int b) {
    const int p[] = {2, 3, 2, 5, 3, 7, 2, 3, 5};
    const int q[] = {1, 1, 2, 1, 1, 1, 3, 2, 1};
    // the only prime we need to consider
    mod = q[b - 2];
    int res = solve(n, k, p[b - 2]);
    mod = MOD;
    res = solve(n, k, p[b - 2]) - res;
    res = (i64)res * inv(q[b - 2]) % mod;
    return (res + mod) % mod;
  }
};
