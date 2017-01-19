#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

class Tunnels {
  int n, m;
  inline void checkMin(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
  inline void checkMax(int &lhs, int rhs) { if (rhs > lhs) lhs = rhs; }
  int l[N], r[N];
  int f[N][N][N];
  int deg[N][N], id[N][N], top[N * N], bot[N * N], tot;
  std::vector<std::string> a;
  bool lu[N], ld[N], ru[N], rd[N], lr[N];
  void dfs(int i, int j) {
    // flood fill
    checkMin(top[tot], i);
    checkMax(bot[tot], i);
    // the top most point and the bottom most point
    id[i][j] = tot;
    for (int k = 0; k < 4; ++k) {
      int x = i + dx[k], y = j + dy[k];
      if (0 <= x && x < n && 0 <= y && y < m && a[x][y] == 'X' && !id[x][y]) dfs(x, y);
    }
  }
  int dp() {
    // use dp to match the parentheses
    memset(f, -0x3f, sizeof f);
    f[n][0][0] = 0;
    for (int i = n - 1; i >= 0; --i) {
      for (int p = 0; p <= i; ++p) {
        for (int q = 0; q <= i; ++q) {
          // considering i-th row
          // the left side prefix sum is p, the right side one is q
          for (int x = -1; x <= 1; ++x) {
            if (x == 1 && !lu[i]) continue;
            if (x == -1 && !ld[i]) continue;
            if (p - x < 0) continue;
            for (int y = -1; y <= 1; ++y) {
              if (y == 1 && !ru[i]) continue;
              if (y == -1 && !rd[i]) continue;
              if (q - y < 0) continue;
              if (lr[i] && x && x == y) continue;
              checkMax(f[i][p][q], f[i + 1][p - x][q - y] + (x == -1) + (y == -1));
            }
          }
        }
      }
    }
    return f[0][0][0];
  }
 public:
  int minimumTunnels(vector<string> _a) {
    a = _a;
    n = a.size();
    m = a[0].length();
    memset(deg, 0, sizeof deg);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        for (int k = 0; k < 4; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (0 <= x && x < n && 0 <= y && y < m && a[x][y] == 'X') ++deg[i][j];
        }
      }
    }
    memset(top, 0x3f, sizeof top);
    memset(bot, -1, sizeof bot);
    tot = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (!id[i][j] && a[i][j] == 'X') ++tot, dfs(i, j);
    if (m == 1) return tot > 0;
    memset(lu, 0, sizeof lu);
    memset(ld, 0, sizeof ld);
    memset(ru, 0, sizeof ru);
    memset(rd, 0, sizeof rd);
    memset(lr, 0, sizeof lr);
    // lu, ru, ld, rd: the tunnel is connected with the left / right side, and will go  up / down
    // lr: tunnels like #####
    for (int i = 0; i < n; ++i) {
      if (a[i][0] == 'X' && deg[i][0] <= 1) {
        lu[i] = (i == top[id[i][0]]);
        ld[i] = (i == bot[id[i][0]]);
      }
      if (a[i][m - 1] == 'X' && deg[i][m - 1] <= 1) {
        ru[i] = (i == top[id[i][m - 1]]);
        rd[i] = (i == bot[id[i][m - 1]]);
      }
    }
    for (int i = 1; i + 1 < n; ++i) rd[i + 1] &= !ru[i], ld[i + 1] &= !lu[i];
    for (int i = 0; i < n; ++i) lr[i] = (a[i][0] == 'X' && id[i][0] == id[i][m - 1]);
    for (int i = 1; i < n; ++i) {
      int p = id[i][0], q = id[i][m - 1];
      if (p && p != q && top[p] == bot[p]) ld[i] = false;
      if (q && p != q && top[q] == bot[q]) rd[i] = false;
    }
    return tot - dp();
  }
};
