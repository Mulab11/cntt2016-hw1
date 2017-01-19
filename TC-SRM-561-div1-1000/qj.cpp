#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, M = 300 + 10, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

class Orienteering {
  int id[N][N], cnt, tot;
  std::vector<int> adj[N * N];
  int dist[M][M];
  int size[N * N];
  void dfs(int a, int fa, int r, int d) {
    if (a <= cnt) dist[r][a] = d, size[a] = 1; else size[a] = 0;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      if (b != fa) dfs(b, a, r, d + 1), size[a] += size[b];
    }
  }
  double f[N * N];
 public:
  double expectedLength(vector<string> s, int k) {
    if (k == 1) return 0.;
    // ans = E[euler tour] - E[diameter]
    const int n = s.size(), m = s[0].length();
    memset(id, 0, sizeof id);
    tot = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (s[i][j] == '*') id[i][j] = ++tot;
    cnt = tot;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (s[i][j] == '.') id[i][j] = ++tot;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int a = id[i][j];
        if (!a) continue;
        for (int p = 0; p < 4; ++p) {
          int x = i + dx[p], y = j + dy[p];
          if (0 <= x && x < n && 0 <= y && y < m) {
            int b = id[x][y];
            if (b) adj[a].push_back(b);
          }
        }
      }
    }
    for (int i = 1; i <= cnt; ++i)
      dfs(i, 0, i, 0);
    f[cnt] = 1.;
    for (int i = cnt - 1; i >= 0; --i) f[i] = f[i + 1] / (i + 1.) * (i - k + 1.);
    // f[i] = C(i, k) / C(cnt, k)
    dfs(1, 0, 1, 0);
    double res = 0.;
    for (int i = 2; i <= tot; ++i) res += 1. - f[size[i]] - f[cnt - size[i]];
    // res = E[length of the euler tour of all selected vertecies]
    f[cnt] = 1.;
    for (int i = cnt - 1; i >= 0; --i) f[i] = f[i + 1] / (i + 1.) * (i - (k - 2) + 1.);
    // f[i] = C(i, k - 2) / C(cnt, k - 2)
    double temp = 0.;
    for (int i = 1; i <= cnt; ++i) {
      for (int j = i + 1; j <= cnt; ++j) {
        // enumerate the diameter
        int cur = 0;
        for (int k = 1; k <= cnt; ++k) {
          if (k == i || k == j) continue;
          bool flag = false;
          if (dist[i][k] > dist[i][j] || (dist[i][k] == dist[i][j] && k < j)) flag = true;
          if (dist[j][k] > dist[i][j] || (dist[j][k] == dist[i][j] && k < i)) flag = true;
          if (flag) ++cur;
        }
        temp += dist[i][j] * f[cnt - cur - 2];
      }
    }
    temp = temp * k * (k - 1.) / (cnt - k + 1.) / (cnt - k + 2.);
    res = 2. * res - temp;
    return res;
  }
};
