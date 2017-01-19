#include <bits/stdc++.h>

using namespace std;

class TheBrickTowerMediumDivOne {
  static const int N = 50, INF = 0x3f3f3f3f;
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
  int solve(std::vector<int> h, int m) {
    const int n = h.size();
    std::sort(h.begin(), h.end());
    static int f[N][N][2];
    memset(f, 0x3f, sizeof f);
    f[0][0][0] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= n; ++j) {
        for (int k = 0; k < 2; ++k) {
          int cur = f[i][j][k];
          if (cur == INF) continue;
          // merge two blocks
          if (j > 1) check(f[i + 1][j - 1][k], cur + 2 * h[i]);
          if (j) {
            // merge one block with the leftist block
            check(f[i + 1][j - 1][1], cur + h[i] + std::max(h[i], k ? h[i] : m));
            // put it next to a block
            check(f[i + 1][j][k], cur + h[i]);
          }
          // put it next to the leftist block
          check(f[i + 1][j][1], cur + std::max(h[i], k ? h[i] : m));
          // insert a new block
          check(f[i + 1][j + 1][k], cur);
        }
      }
    }
    return std::min(f[n][0][0], f[n][0][1]);
  }
 public:
  vector<int> find(vector<int> h) {
    const int n = h.size();
    std::vector<int> res;
    int val = solve(h, 50) - 50;
    std::vector<bool> flag(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (flag[j]) continue;
        std::vector<int> temp;
        for (int k = 0; k < n; ++k) if (k != j && !flag[k]) temp.push_back(h[k]);
        int t = i ? std::max(h[j], h[res[i - 1]]) : 0;
        if (solve(temp, h[j]) + t == val) {
          flag[j] = true;
          val -= t;
          res.push_back(j);
          break;
        }
      }
    }
    return res;
  }
};
