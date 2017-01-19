#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 50 + 10;

class AstronomicalRecords {
  int f[N][N];
  int solve(const std::vector<int> &a, const std::vector<int> &b, int p, int q) {
    // calculate the LCS
    memset(f, 0, sizeof f);
    for (int i = 0; i < a.size(); ++i)
      for (int j = 0; j < b.size(); ++j)
        f[i + 1][j + 1] = std::max(std::max(f[i][j + 1], f[i + 1][j]), f[i][j] + ((i64)a[i] * p == (i64)b[j] * q));
    return f[a.size()][b.size()];
  }
 public:
  int minimalPlanets(vector<int> a, vector<int> b) {
    // enumerate the size ratio between two observations
    int res = 0;
    for (int i = 0; i < a.size(); ++i)
      for (int j = 0; j < b.size(); ++j)
        res = std::max(res, solve(a, b, b[j], a[i]));
    return a.size() + b.size() - res;
  }
};
