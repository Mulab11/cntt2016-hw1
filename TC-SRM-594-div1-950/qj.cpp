#include <bits/stdc++.h>

using namespace std;

class FoxAndAvatar {
  int m, ans;
  void dfs(int n, int p, int dep) {
    // keep in mind: when p is a constant, answer will never decrease as n increases.
    if (n == 1) {
      if (dep < ans) ans = dep; // update answer
      return;
    }
    if (dep + 1 >= ans) return;
    int x = p / m, y = p % m;
    int r = (n - 1) / m, c = (n - 1) % m;
    if ((p == n - 1 && (x == 0 || y == 0)) || (p == 0 && (r == 0 || m == 1)) || (p == m - 1 && n < 2 * m)) {
      // check if we can succeed in one step
      ans = dep + 1;
      return;
    }
    if (dep + 2 >= ans) return;
    // remove a i x j rectangle in which all people are above x
    for (int i = 1; i <= x; ++i)
      for (int j = 1; j <= m; ++j)
        dfs(n - i * j, p - i * j, dep + 1);
    // remove all people under x
    if ((x + 1) * m < n) dfs((x + 1) * m, p, dep + 1);
    // remove a rectangle on the left side of x
    for (int i = 0; i <= x; ++i)
      for (int j = 0; j < y; ++j)
        dfs(n - (r - i) * (j + 1) - std::min(c + 1, j + 1), p - (x - i + 1) * (j + 1), dep + 1);
    // remove a rectangle on the right side of x
    for (int i = 0; i <= x; ++i)
      for (int j = y + 1; j < m; ++j)
        if (i * m + j < n) dfs(n - (r - i) * (j - y) - std::max(std::min(j, c) - y, 0), p - (x - i) * (j - y), dep + 1);
  }
 public:
  int minimalSteps(int q, int w, int x) {
    m = w;
    ans = 4; // it's obvious that we can remove all other people within four steps
    dfs(q, x - 1, 0);
    return ans;
  }
};
