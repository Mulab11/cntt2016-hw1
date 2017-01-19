#include <bits/stdc++.h>

using namespace std;

class FoxAndFlowerShopDivOne {
  static const int N = 30 + 10, M = 900 + 10;
  int dispatch(char c) {
    switch (c) {
      case 'L': return 1;
      case 'P': return -1;
      default: return 0;
    }
  }
  inline int calc(int a[][N], int u, int d, int l, int r) {
    // submatrix sum
    return a[d][r] - a[d][l] - a[u][r] + a[u][l];
  }
  inline void check(int &lhs, int rhs) { if (rhs > lhs) lhs = rhs; }
  int solve(const std::vector<std::string> &s, int k) {
    const int n = s.size(), m = s[0].length();
    static int f[N][2 * M], g[N][2 * M], cnt[N][N], sum[N][N];
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    memset(cnt, 0, sizeof cnt);
    memset(sum, 0, sizeof sum);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int c = dispatch(s[i][j]);
        sum[i + 1][j + 1] = c + sum[i][j + 1] + sum[i + 1][j] - sum[i][j];
        cnt[i + 1][j + 1] = abs(c) + cnt[i][j + 1] + cnt[i + 1][j] - cnt[i][j];
      }
    }
    // prefix max
    for (int i = 0; i < n; ++i) {
      memcpy(f[i + 1], f[i], sizeof f[i]);
      for (int j = 0; j <= i; ++j)
        for (int l = 0; l < m; ++l)
          for (int r = l + 1; r <= m; ++r)
            check(f[i + 1][calc(sum, j, i + 1, l, r) + M], calc(cnt, j, i + 1, l, r));
    }
    // suffix max
    for (int i = n - 1; i >= 0; --i) {
      memcpy(g[i], g[i + 1], sizeof g[i]);
      for (int j = i + 1; j <= n; ++j)
        for (int l = 0; l < m; ++l)
          for (int r = l + 1; r <= m; ++r)
            check(g[i][calc(sum, i, j, l, r) + M], calc(cnt, i, j, l, r));
    }
    int res = -1;
    // enumerate the seperator
    for (int i = 1; i < n; ++i) {
      for (int a = 0; a < 2 * M; ++a) {
        if (f[i][a] == -1) continue;
        for (int b = 0; b < 2 * M; ++b)
          if (abs(a + b - 2 * M) <= k && g[i][b] != -1) check(res, f[i][a] + g[i][b]);
      }
    }
    return res;
  }
  std::vector<std::string> transpose(const std::vector<std::string> &s) {
    // A -> A^T
    const int n = s.size(), m = s[0].length();
    std::vector<std::string> res(m, std::string(n, 0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        res[j][i] = s[i][j];
    return res;
  }
 public:
  int theMaxFlowers(vector<string> s, int k) {
    return std::max(solve(s, k), solve(transpose(s), k));
  }
};
