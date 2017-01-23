#include <bits/stdc++.h>

using namespace std;

class EllysChessboard {
  static const int N = 15, INF = 0x3f3f3f3f;
  int mem[N][N][N][N];
  std::vector<int> x, y;
  int solve(int l, int r, int u, int d) {
    int &res = mem[l][r][u][d];
    if (res < INF) return res;
    bool flag = true;
    for (int i = 0; i < x.size(); ++i) {
      if (l <= x[i] && x[i] <= r && d <= y[i] && y[i] <= u) continue;
      // enumerate one of the new points to be added
      flag = false;
      int cur = std::max(std::max(abs(x[i] - l), abs(x[i] - r)), std::max(abs(y[i] - u), abs(y[i] - d)));
      int a = std::min(l, x[i]), b = std::max(r, x[i]), p = std::min(d, y[i]), q = std::max(u, y[i]);
      cur += solve(a, b, q, p); // new rectangle
      for (int j = 0; j < x.size(); ++j) {
        if (l <= x[j] && x[j] <= r && d <= y[j] && y[j] <= u) continue;
        if (j == i) continue;
        if (a <= x[j] && x[j] <= b && p <= y[j] && y[j] <= q)
          cur += std::max(std::max(abs(x[j] - a), abs(x[j] - b)), std::max(abs(y[j] - p), abs(y[j] - q)));
      }
      res = std::min(res, cur);
    }
    if (flag) res = 0;
    return res;
  }
 public:
  int minCost(vector<string> s) {
    for (int i = 0; i < 8; ++i)
      for (int j = 0; j < 8; ++j)
        if (s[i][j] == '#') x.push_back(i + j), y.push_back(i - j + 8);
    // rotate the coordinate
    // now the Manhattan distance become Chebyshev distance
    if (x.empty()) return 0;
    memset(mem, 0x3f, sizeof mem);
    int res = INF;
    for (int i = 0; i < x.size(); ++i) res = std::min(res, solve(x[i], x[i], y[i], y[i]));
    return res;
  }
};
