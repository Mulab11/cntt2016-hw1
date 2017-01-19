#include <bits/stdc++.h>

using namespace std;
const int N = 5000 + 10, E = 100 * N, INF = 10000000;

class Flow {
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

class OldBridges {
  Flow g;
 public:
  string isPossible(vector<string> a, int a1, int a2, int an, int b1, int b2, int bn) {
    const int n = a.size(), s = n + 1, t = s + 1;
    g.clear(s, t);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (a[i][j] == 'O') g.link(i, j, 2); else if (a[i][j] == 'N') g.link(i, j, INF);
    g.link(s, a1, 2 * an);
    g.link(a2, t, 2 * an);
    g.link(s, b1, 2 * bn);
    g.link(b2, t, 2 * bn);
    if (g.flow() < 2 * (an + bn)) return "No";
    g.clear(s, t);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (a[i][j] == 'O') g.link(i, j, 2); else if (a[i][j] == 'N') g.link(i, j, INF);
    g.link(s, a1, 2 * an);
    g.link(a2, t, 2 * an);
    g.link(s, b2, 2 * bn);
    g.link(b1, t, 2 * bn);
    return g.flow() < 2 * (an + bn) ? "No" : "Yes";
  }
};
