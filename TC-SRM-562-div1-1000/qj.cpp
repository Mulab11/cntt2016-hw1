#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class InducedSubgraphs {
  // there are 2 cases
  static const int N = 40 + 10, MOD = 1000000009;
  int n, m;
  std::vector<int> adj[N];
  int dist[N][N];
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
  int size[N][N], g[N][N];
  int fact[N], ifact[N], inv[N];
  void dfsA(int a, int fa) {
    int &s = size[a][fa];
    if (s) return;
    int &res = g[a][fa] = 1;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      if (b == fa) continue;
      dfsA(b, a);
      res = (i64)res * g[b][a] % MOD * ifact[size[b][a]] % MOD;
      s += size[b][a];
    }
    res = (i64)res * fact[s++] % MOD;
  }
  int solveA() {
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
    int res = 0;
    for (int a = 0; a < n; ++a) {
      for (int b = 0; b < n; ++b) {
        if (dist[a][b] == n - 2 * m + 1) {
          int cur = 1;
          for (int i = 0; i < adj[a].size(); ++i) {
            int c = adj[a][i];
            if (dist[c][b] < dist[a][b]) {
              dfsA(a, c);
              if (size[a][c] == m) cur = (i64)cur * g[a][c] % MOD; else cur = 0;
              break;
            }
          }
          for (int i = 0; i < adj[b].size(); ++i) {
            int c = adj[b][i];
            if (dist[c][a] < dist[b][a]) {
              dfsA(b, c);
              if (size[b][c] == m) cur = (i64)cur * g[b][c] % MOD; else cur = 0;
              break;
            }
          }
          add(res, cur);
        }
      }
    }
    return res;
  }
  int binom(int n, int m) {
    if (m > n) return 0;
    return (i64)fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
  }
  void merge(int a[][N], int b[][N], int l, int r) {
    static int res[N][N];
    memset(res, 0, sizeof res);
    for (int x = 0; x <= l; ++x) {
      for (int y = 0; x + y <= l; ++y) {
        int cur = a[x][y];
        if (!cur) continue;
        for (int u = 0; u <= r; ++u)
          for (int v = 0; u + v <= r; ++v)
            if (b[u][v]) add(res[x + u][y + v], (i64)cur * binom(x + u, x) % MOD * binom(y + v, v) % MOD * b[u][v]);
      }
    }
    memcpy(a, res, sizeof res);
  }
  int f[N][N][N][N];
  bool flag[N][N];
  void dfsB(int a, int fa) {
    if (flag[a][fa]) return;
    flag[a][fa] = true;
    memset(f[a][fa], 0, sizeof f[a][fa]);
    f[a][fa][0][0] = 1;
    int s = 0;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      if (b == fa) continue;
      dfsB(b, a);
      int t = size[b][a];
      merge(f[a][fa], f[b][a], s += t, t);
    }
    ++s;
    dfsA(a, fa);
    f[a][fa][0][s] = f[a][fa][s][0] = g[a][fa];
  }
  int solveB() {
    memset(flag, 0, sizeof flag);
    int res = 0;
    const int r = n - m, b = n - m;
    for (int i = 0; i < n; ++i) dfsB(i, n), add(res, f[i][n][r][b]);
    res = (i64)res * fact[n - r - b - 1] % MOD;
    return res;
  }
 public:
  int getCount(vector<int> a, vector<int> b, int k) {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = (i64)fact[i - 1] * i % MOD;
    inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = ((i64)MOD - MOD / i) * inv[MOD % i] % MOD;
    ifact[0] = 1;
    for (int i = 1; i < N; ++i) ifact[i] = (i64)ifact[i - 1] * inv[i] % MOD;
    memset(dist, 0x3f, sizeof dist);
    n = a.size() + 1, m = k;
    if (m == 1) return fact[n];
    for (int i = 0; i < a.size(); ++i) adj[a[i]].push_back(b[i]), adj[b[i]].push_back(a[i]), dist[a[i]][b[i]] = dist[b[i]][a[i]] = 1;
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    memset(size, 0, sizeof size);
    return 2 * m <= n ? solveA() : solveB();
  }
};
