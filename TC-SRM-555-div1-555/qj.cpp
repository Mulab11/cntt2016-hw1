#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class XorBoard {
  static const int N = 3200 + 10, MOD = 555555555;
  int binom[N][N];
 public:
  int count(int n, int m, int r, int c, int s) {
    binom[0][0] = 1;
    for (int i = 1; i < N; ++i)
      for (int j = 0; j < N; ++j)
        binom[i][j] = (binom[i - 1][j] + (j ? binom[i - 1][j - 1] : 0)) % MOD;
    int res = 0;
    for (int a = r & 1; a <= n && a <= r; a += 2) { // number of rows that are operated odd number times
      for (int b = c & 1; b <= m && b <= c; b += 2) { // number of columns ...
        if (a * (m - b) + b * (n - a) != s) continue;
        int x = (r - a) / 2, y = (c - b) / 2;
        res = (res + (i64)binom[n][a] * binom[x + n - 1][n - 1] % MOD * binom[m][b] % MOD * binom[y + m - 1][m - 1]) % MOD; // do combinatorics
      }
    }
    return (res + MOD) % MOD;
  }
};
