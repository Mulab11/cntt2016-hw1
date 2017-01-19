#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 10, E = 100 * N, INF = 0x3f3f3f3f;

class Flow { // maximal flow
  int adj[N], to[E], next[E], cap[E], cnt;
  int h[N], gap[N], s, t;
  int dfs(int a, int df) {
    if (a == t) return df;
    int res = 0;
    for (int i = adj[a]; i; i = next[i]) {
      int b = to[i];
      if (cap[i] && h[a] == h[b] + 1) {
        int f = dfs(b, std::min(df - res, cap[i]));
        cap[i] -= f;
        cap[i ^ 1] += f;
        res += f;
      }
      if (res == df) return res;
    }
    if (--gap[h[a]] == 0) h[s] = t + 1;
    ++gap[++h[a]];
    return res;
  }
 public:
  inline void clear(int _s, int _t) {
    cnt = 2, s = _s, t = _t;
    memset(adj, 0, sizeof adj);
  }
  inline void link(int a, int b, int c) {
    to[cnt] = b, next[cnt] = adj[a], cap[cnt] = c, adj[a] = cnt++;
    to[cnt] = a, next[cnt] = adj[b], cap[cnt] = 0, adj[b] = cnt++;
  }
  int flow() {
    memset(h, 0, sizeof h);
    memset(gap, 0, sizeof gap);
    int res = 0;
    while (h[s] < t + 1) res += dfs(s, INF);
    return res;
  }
};

class TheTilesDivOne {
  int n, m;
  inline int pos(int x, int y) { return x * m + y; }
  Flow g;
 public:
  int find(vector<string> a) {
    n = a.size(), m = a[0].length();
    const int tot = n * m, s = 2 * tot, t = s + 1, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
    g.clear(s, t);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == 'X') continue;
        if (!((i + j) & 1)) {
          g.link(pos(i, j), pos(i, j) + tot, 1);
          continue;
        }
        if (j & 1) g.link(s, pos(i, j), 1); else g.link(pos(i, j), t, 1); // bicoloring again
        for (int k = 0; k < 4; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (0 <= x && x < n && 0 <= y && y < m && a[x][y] == '.') (j & 1) ? g.link(pos(i, j), pos(x, y), 1) : g.link(pos(x, y) + tot, pos(i, j), 1);
        }
      }
    }
    return g.flow();
  }
};
