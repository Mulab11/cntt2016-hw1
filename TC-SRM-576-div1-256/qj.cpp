#include <bits/stdc++.h>

using namespace std;

class ArcadeManao {
  static const int N = 50 + 10;
  bool flag[N][N];
  int n, m;
  std::vector<std::string> a;
  int h;
  bool dfs(int x, int y) {
    if (a[x][y] != 'X') return false;
    if (x == n - 1) return true; // we arrived the floor
    if (flag[x][y]) return false;
    flag[x][y] = true;
    for (int t = 0; t < n; ++t) if (abs(x - t) <= h && dfs(t, y)) return true;
    if (y && dfs(x, y - 1)) return true;
    if (y + 1 < m && dfs(x, y + 1)) return true;
    return false;
  }
 public:
  int shortestLadder(vector<string> _a, int x, int y) {
    a = _a;
    n = a.size();
    m = a[0].length();
    for (h = 0;; ++h) if (memset(flag, 0, sizeof flag), dfs(x - 1, y - 1)) return h; // enumerate the height of the laddar
  }
};
