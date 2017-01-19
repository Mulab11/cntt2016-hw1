#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 50 + 10;

class Excavations {
  int n, m;
  i64 f[2][N][2][N][N];
  void discretize(std::vector<int> &a) {
    std::vector<int> temp = a;
    temp.push_back(0);
    std::sort(temp.begin(), temp.end());
    temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
    m = temp.size();
    for (int i = 0; i < a.size(); ++i) a[i] = std::lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin();
  }
 public:
  i64 count(vector<int> a, vector<int> b, vector<int> c, int k) {
    discretize(b);
    std::vector< std::pair<int, int> > info;
    n = a.size();
    for (int i = 0; i < n; ++i) info.push_back(std::make_pair(a[i], b[i]));
    std::sort(info.begin(), info.end());
    memset(f, 0, sizeof f);
    f[0][0][0][0][m] = 1;
    // it's obvious that all valid D will make a interval
    // f[i][j][2][l][r]: number of ways that
    //   considering the i-th element
    //   we have chosen j elements
    //   2: whether a element of this kind has been chosen
    //   the valid D is in [l, r]
    // roll the DP array to avoid MLE
    std::vector<bool> flag(n);
    for (int i = 0; i < n; ++i) flag[i] = (std::find(c.begin(), c.end(), info[i].first) != c.end());
    for (int i = 0;; ++i) {
      int p = i & 1;
      if (i && (i == n || info[i].first != info[i - 1].first)) {
        // new type
        for (int j = 0; j <= i && j <= k; ++j) {
          for (int l = 0; l < m; ++l) {
            for (int r = l + 1; r <= m; ++r) {
              if (flag[i - 1]) f[p][j][0][l][r] = f[p][j][1][l][r]; else f[p][j][0][l][r] += f[p][j][1][l][r];
              f[p][j][1][l][r] = 0;
            }
          }
        }
      }
      if (i == n) break;
      int t = info[i].second;
      memset(f[!p], 0, sizeof f[!p]);
      for (int j = 0; j <= i && j <= k; ++j) {
        for (int q = 0; q < 2; ++q) {
          for (int l = 0; l < m; ++l) {
            for (int r = l + 1; r <= m; ++r) {
              i64 cur = f[p][j][q][l][r];
              if (!cur) continue;
              f[!p][j][q][l][r] += cur;
              int x = l, y = r;
              if (flag[i] && !q) x = std::max(x, t);
              if (!flag[i]) y = std::min(y, t);
              if (x < y) f[!p][j + 1][1][x][y] += cur;
            }
          }
        }
      }
    }
    i64 res = 0;
    for (int c = 0; c < 2; ++c)
      for (int l = 0; l < m; ++l)
        for (int r = l + 1; r <= m; ++r)
          res += f[n & 1][k][c][l][r];
    return res;
  }
};
