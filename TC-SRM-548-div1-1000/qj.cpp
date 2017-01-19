#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class KingdomAndCities {
  static const int N = 50 + 10, M = N * N, MOD = 1000000007;
  int power(int base, int exp) {
    int res = 1;
    for (; exp; exp >>= 1) {
      if (exp & 1) res = (i64)res * base % MOD;
      base = (i64)base * base % MOD;
    }
    return res;
  }
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
  int binom[M][M];
  int f[N][N][3], g[N][N][3];
 public:
  int howMany(int n, int m, int k) {
    memset(binom, 0, sizeof binom);
    binom[0][0] = 1;
    for (int i = 1; i < M; ++i)
      for (int j = 0; j < M; ++j)
        binom[i][j] = (binom[i - 1][j] + (j ? binom[i - 1][j - 1] : 0)) % MOD;
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    // g[n][k][m] : number of graphs
    // f[n][k][m] : number of connected graphs
    for (int i = 1; i < N; ++i) {
      for (int j = 0; j <= k; ++j) {
        f[i][j][0] = g[i][j][0] = binom[binom[i][2]][j];
        if (j > 1) f[i][j][1] = g[i][j][1] = (i64)binom[binom[i - 1][2]][j - 2] * binom[i - 1][2] % MOD;
        if (i > 1) {
          int &cur = g[i][j][2] = 0;
          if (j > 3) add(cur, (i64)binom[binom[i - 2][2]][j - 4] * binom[i - 2][2] % MOD * binom[i - 2][2]);
          if (j > 2) add(cur, (i64)binom[binom[i - 2][2]][j - 3] * (i - 2) % MOD * (i - 2));
          f[i][j][2] = g[i][j][2];
        }
        for (int a = 1; a < i; ++a) {
          for (int b = 0; b <= j; ++b) {
            add(f[i][j][0], (i64)-binom[i - 1][a - 1] * f[a][b][0] % MOD * g[i - a][j - b][0]);
            add(f[i][j][1], (i64)-binom[i - 1][a - 1] * f[a][b][1] % MOD * g[i - a][j - b][0]);
            if (i > 1) {
              add(f[i][j][2], (i64)-binom[i - 2][a - 1] * f[a][b][1] % MOD * g[i - a][j - b][1]);
              if (a > 1) add(f[i][j][2], (i64)-binom[i - 2][a - 2] * f[a][b][2] % MOD * g[i - a][j - b][0]);
            }
          }
        }
      }
    }
    int res = f[n][k][m];
    return (res + MOD) % MOD;
  }
};
