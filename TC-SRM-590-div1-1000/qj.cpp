#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 10, E = 100 * N, INF = 0x3f3f3f3f;

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

class FoxAndCity {
  Flow flow;
  int n, s, t;
  std::vector<std::string> adj;
  std::vector<int> d, dist;
  void bfs() {
    std::vector<int> q;
    q.push_back(0);
    dist[0] = 0;
    for (int i = 0; i < q.size(); ++i) {
      int a = q[i];
      for (int b = 0; b < n; ++b) if (adj[a][b] == 'Y' && dist[b] == -1) q.push_back(b), dist[b] = dist[a] + 1;
    }
  }
  inline int sqr(int x) { return x * x; }
  inline int pos(int x, int y) { return y == n ? t : (x * n + y); } // the position of the y-th vertex of node x
 public:
  int minimalCost(vector<string> _a, vector<int> _d) {
    adj = _a, d = _d;
    dist.resize(n = adj.size(), -1);
    bfs();
    s = n * n, t = s + 1;
    flow.clear(s, t);
    for (int i = 0; i < n; ++i) {
      if (i) {
        for (int j = 0; j < n; ++j) flow.link(pos(i, j), pos(i, j + 1), j ? sqr(j - d[i]) : INF); // the cost of setting dist[i] to j
      } else {
        // dist[0] = 0
        for (int j = 0; j < n; ++j) flow.link(pos(i, j), pos(i, j + 1), j ? INF : 0);
      }
      flow.link(s, i * n, INF);
      for (int j = 0; j < n; ++j) {
        if (adj[i][j] == 'N') continue;
        //dist[j] <= dist[i] + 1
        for (int k = 0; k < n; ++k) flow.link(pos(j, k + 1), pos(i, k), INF);
      }
      flow.link(pos(i, dist[i] + 1), t, INF);
    }
    return flow.flow();
  }
};
