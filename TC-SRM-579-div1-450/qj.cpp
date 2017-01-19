#include <bits/stdc++.h>

using namespace std;

class TravellingPurchasingMan {
  static const int N = 50 + 10, M = 16, INF = 0x3f3f3f3f;
  int dist[N][N];
  int l[N], r[N], d[N];
  int f[1 << M][M];
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  int maxStores(int n, vector<string> t, vector<string> s) {
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (int i = 0; i < s.size(); ++i) {
      int a, b, c;
      sscanf(s[i].c_str(), "%d%d%d", &a, &b, &c);
      check(dist[a][b], c);
      check(dist[b][a], c);
    }
    // transitive closure
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          check(dist[i][j], dist[i][k] + dist[k][j]);
    const int m = t.size();
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < m; ++i) sscanf(t[i].c_str(), "%d%d%d", &l[i], &r[i], &d[i]);
    for (int i = 0; i < m; ++i) if (dist[n - 1][i] <= r[i]) check(f[1 << i][i], std::max(dist[n - 1][i], l[i]) + d[i]);
    int res = 0;
    for (int s = 0; s < (1 << m); ++s) {
      // steiner tree
      // f[s][i]:
      //    we are at vertex i, the set of vertices we have visited is S
      //    the minimum possible current time
      int c = __builtin_popcount(s);
      for (int a = 0; a < m; ++a) {
        int cur = f[s][a];
        if (cur == INF) continue;
        res = std::max(res, c);
        for (int b = 0; b < m; ++b) {
          if (s >> b & 1) continue;
          int t = f[s][a] + dist[a][b];
          if (t <= r[b]) check(f[s | (1 << b)][b], std::max(t, l[b]) + d[b]);
        }
      }
    }
    return res;
  }
};
