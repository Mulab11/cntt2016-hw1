#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class SkiResorts {
  static const int N = 50 + 10;
  static const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
  i64 f[N][N];
  inline void check(i64 &lhs, i64 rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  i64 minCost(vector<string> s, vector<int> a) {
    std::vector<int> b = a;
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    const int n = a.size();
    for (int i = 0; i < n; ++i) a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < b.size(); ++i) f[n - 1][i] = llabs(b[a[n - 1]] - b[i]);
    // f[i][j]: change the altitude of the i-th vertex to the j-th alitude
    for (int cnt = n + 10; cnt--;) { // bellman-ford
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          if (s[x][y] == 'N') continue;
          i64 temp = INF;
          for (int v = 0; v < b.size(); ++v) {
            check(temp, f[x][v]);
            check(f[y][v], temp + llabs(b[v] - b[a[y]]));
          }
        }
      }
    }
    i64 res = *std::min_element(f[0], f[0] + b.size());
    return res == INF ? -1 : res;
  }
};
