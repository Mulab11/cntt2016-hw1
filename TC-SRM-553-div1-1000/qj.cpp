#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class YamanoteLine {
  static const int N = 50 + 10;
  static const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
  i64 f[N][N][2 * N];
  void check(i64 &lhs, i64 rhs) { if (rhs < lhs) lhs = rhs; }
  void solve(i64 res[], const i64 lhs[], const i64 rhs[]) {
    for (int i = 0; i < 2 * N; ++i) {
      if (lhs[i] == INF) continue;
      for (int j = std::max(N - i, 0); i + j - N < 2 * N; ++j)
        if (rhs[j] < INF) check(res[i + j - N], lhs[i] + rhs[j]);
    }
  }
 public:
  i64 howMany(int n, vector<int> s1, vector<int> t1, vector<int> l1, vector<int> s2, vector<int> t2, vector<int> l2) {
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < s1.size(); ++i) {
      int a = s1[i], b = t1[i], c = l1[i];
      if (a <= b) {
        // d[b] - d[a] >= c
        // d[a] - d[b] <= -c
        check(f[b][a][N], -c);
      } else {
        // x - d[a] + d[b] >= c
        // d[b] - d[a] >= c - x
        // d[a] - d[b] <= x - c
        check(f[b][a][N + 1], -c);
      }
    }
    for (int i = 0; i < s2.size(); ++i) {
      int a = s2[i], b = t2[i], c = l2[i];
      if (a <= b) {
        // d[b] - d[a] <= c
        check(f[a][b][N], c);
      } else {
        // x - d[a] + d[b] <= c
        // d[b] - d[a] <= c - x
        check(f[a][b][N - 1], c);
      }
    }
    for (int i = 0; i < n; ++i) {
      // d[i + 1] - d[i] >= 1
      check(f[i + 1][i][N], -1);
    }
    // d[n] - d[0] <= x
    // d[n] - d[0] >= x
    // d[0] - d[n] <= -x
    check(f[0][n][N + 1], 0);
    check(f[n][0][N - 1], 0);
    for (int i = 0; i <= n; ++i) check(f[i][i][N], 0);
    for (int k = 0; k <= n; ++k)
      for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
          solve(f[i][j], f[i][k], f[k][j]);
    i64 l = n, r = INF;
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j < 2 * N; ++j) {
        i64 k = j - N, y = f[i][i][j];
        //k * x + y >= 0
        // k * x >= -y
        if (k == 0) {
          if (y < 0) return 0;
          continue;
        }
        if (y == INF) continue;
        // x <= -y / k
        if (k < 0) r = std::min(r, -y / k); else l = std::max(l, (-y + k - 1) / k);
      }
    }
    return r == INF ? -1 : (r - l + 1);
  }
};
