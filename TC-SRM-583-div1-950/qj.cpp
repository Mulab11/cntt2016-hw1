#include <bits/stdc++.h>

using namespace std;

const int N = 23;

class RandomPaintingOnABoard {
  int n, m, sum;
  int p[N][N];
  void parse(const std::vector<std::string> &temp) { // input parser
    n = temp.size();
    m = temp[0].length();
    sum = 0;
    if (n > m) {
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
          sum += (p[i][j] = temp[i][j] - '0');
    } else {
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
          sum += (p[j][i] = temp[i][j] - '0');
      std::swap(n, m);
    }
  }
  int f[N][2][9 * N * N], g[N];
 public:
  double expectedSteps(vector<string> _s) {
    parse(_s);
    double res = 0.;
    for (int y = 0; y < (1 << m); ++y) {
      memset(g, 0, sizeof g);
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
          if (y >> j & 1) g[i] += p[i][j]; // sum of the i-th row
      memset(f, 0, sizeof f);
      f[0][__builtin_parity(y) ^ ((n + m) & 1)][0] = 1;
      for (int x = 0; x < n; ++x) {
        for (int p = 0; p < 2; ++p) {
          for (int q = 0; q <= sum; ++q) {
            int cur = f[x][p][q];
            if (!cur) continue;
            f[x + 1][p][q] += cur; // not to choose the i-th row
            f[x + 1][!p][q + g[x]] += cur; // choose the i-th row
          }
        }
      }
      for (int p = 0; p < 2; ++p) {
        for (int q = 0; q < sum; ++q) {
          double z = f[n][p][q] / (1. - (double)q / sum); // sum of geometric sequence
          if (p) res += z; else res -= z; // inclusive-exclusive principal
        }
      }
    }
    return res;
  }
};
