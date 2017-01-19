#include <bits/stdc++.h>

using namespace std;

class EqualSums {
  static const int N = 50 + 10, M = 10, MOD = 1000000007;
  int n;
  std::vector<std::string> s;
  int id[N][2], x[N][2], y[N][2], l[2 * N], r[2 * N], tot;
  bool flag;
  void dfs(int a, int b, int p, int q) {
    if (id[a][b]) {
      if (x[a][b] != p || y[a][b] != q) flag = false;
      return;
    }
    id[a][b] = tot;
    x[a][b] = p, y[a][b] = q;
    // p * t + q >= 0
    if (p > 0) l[tot] = std::max(l[tot], -q); else r[tot] = std::min(r[tot], q); // update the range of the label
    for (int c = 0; c < n; ++c) {
      char ch = (b & 1) ? s[c][a] : s[a][c];
      if (ch == '-') continue;
      int d = ch - '0';
      // px + q + y = d
      // y = d - px - q
      dfs(c, !b, -p, d - q);
    }
  }
 public:
  int count(vector<string> _s) {
    // like weighted bipartite matching
    // we assign every vertex with a label
    // then calculate the range of each label
    s = _s;
    n = s.size();
    memset(id, 0, sizeof id);
    tot = 0;
    flag = true;
    for (int i = 0; i < n; ++i) {
      if (!id[i][0]) {
        ++tot;
        l[tot] = 0, r[tot] = MOD;
        dfs(i, 0, 1, 0);
        if (l[tot] > r[tot]) return 0; // no solution
        break;
      }
    }
    for (int i = 0; i < n; ++i) {
      if (!id[i][1]) {
        ++tot;
        l[tot] = 0, r[tot] = MOD;
        dfs(i, 1, 1, 0);
        if (l[tot] > r[tot]) return 0; // no solution
      }
    }
    if (!flag) return 0;
    static int f[M][M];
    memset(f, 0, sizeof f);
    f[l[1]][r[1]] = 1;
    for (int i = 2; i <= tot; ++i) {
      static int g[M][M];
      memset(g, 0, sizeof g);
      for (int p = l[1]; p <= r[1]; ++p) {
        for (int q = p; q <= r[1]; ++q) {
          int cur = f[p][q];
          if (!cur) continue;
          for (int j = p + l[i]; j <= q + r[i]; ++j) {
            int u = std::max(p, j - r[i]), v = std::min(q, j - l[i]);
            if (u > v) continue;
            (g[u][v] += cur) %= MOD;
          }
        }
      }
      memcpy(f, g, sizeof g);
    }
    int res = 0;
    for (int p = l[1]; p <= r[1]; ++p)
      for (int q = p; q <= r[1]; ++q)
        (res += f[p][q]) %= MOD;
    return res;
  }
};
