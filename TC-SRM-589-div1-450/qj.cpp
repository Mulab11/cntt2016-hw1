#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, E = 1000 * N, INF = 0x3f3f3f3f;

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

class GearsDiv1 {
  std::vector<std::string> a;
  std::string b;
  int n;
  Flow g;
  int solve(char x, char y) {
    // all the gears with the missing color can be reserved
    // calculate the size of bipartite graph's maximum independent set
    int s = n + 1, t = s + 1;
    g.clear(s, t);
    for (int i = 0; i < n; ++i) if (b[i] == x) g.link(s, i, 1); else if (b[i] == y) g.link(i, t, 1);
    for (int i = 0; i < n; ++i) {
      if (b[i] != x) continue;
      for (int j = 0; j < n; ++j) if (b[j] == y && a[i][j] == 'Y') g.link(i, j, INF);
    }
    return g.flow();
  }
 public:
  int getmin(string _b, vector<string> _a) {
    a = _a, b = _b;
    n = a.size();
    return std::min(solve('R', 'G'), std::min(solve('R', 'B'), solve('G', 'B'))); // enumerate all possible pairs of colors
  }
};
