#include <bits/stdc++.h>

using namespace std;

const int N = 8, MOD = 1000000009;

class StringPath {
  int f[2 * N][1 << N][1 << N];
  int n, m, i, x, y, l, r, mask;
  std::string a, b;
  bool flag;
  void dfs(int j, int p, int q, int v) {
    if (!v) return; // pruning
    if (j > r) {
      p &= x | (x << 1);
      q &= y | (y << 1);
      (f[i + 1][p & mask][q & mask] += v) %= MOD;
      return;
    }
    if (flag) {
      dfs(j + 1, p, q, 25LL * v % MOD);
      dfs(j + 1, p | (1 << j), q | (1 << j), v); // the char equals a[j] and b[j]
    } else {
      dfs(j + 1, p, q, 24LL * v % MOD); // the char here isn't equal to a[j] or b[j]
      dfs(j + 1, p | (1 << j), q, v); // the char equals a[j]
      dfs(j + 1, p, q | (1 << j), v); // the char equals b[j]
    }
  }
 public:
  int countBoards(int _n, int _m, string _a, string _b) {
    n = _n, m = _m, a = _a, b = _b;
    memset(f, 0, sizeof f);
    f[0][1][1] = 1;
    for (i = 0; i < n + m - 1; ++i) {
      // f[i][p][q]: we are to determine the i-th diagonal,
      // p: whether there is a path from the starting point to the diagonal that matches a,
      // q: whether there is a path that matchs b
      flag = (a[i] == b[i]); // corner case
      l = std::max(0, i - (n - 1));
      r = std::min(m - 1, i);
      mask = ((1 << (r + 1)) - 1) & ~((1 << l) - 1);
      for (x = 0; x < (1 << m); ++x)
        for (y = 0; y < (1 << m); ++y)
          dfs(l, 0, 0, f[i][x][y]);
    }
    return f[n + m - 1][1 << (m - 1)][1 << (m - 1)];
  }
};
