#include <bits/stdc++.h>

using namespace std;

class TheExperiment {
  static const int N = 300 + 10, MOD = 1000000009;
  int f[N][N][3], sum[N];
  inline void add(int &lhs, int rhs) { lhs = (lhs + rhs) % MOD; }
 public:
  int countPlacements(vector<string> _s, int m, int l, int a, int b) {
    std::string s;
    for (int i = 0; i < _s.size(); ++i) s += _s[i];
    const int n = s.length();
    for (int i = 0; i < n; ++i) sum[i + 1] = sum[i] + s[i] - '0'; // prefix sum
    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= m; ++j) {
        for (int k = 0; k < 3; ++k) {
          int cur = f[i][j][k];
          if (!cur) continue;
          if (k == 0 || k == 2) add(f[i + 1][j][0], cur);
          for (int t = 1; t <= l && i + t <= n; ++t) // the length of current interval
            if (a <= sum[i + t] - sum[i] && sum[i + t] - sum[i] <= b)
              add(f[i + t][j + 1][std::max(k, t == l ? 2 : 1)], cur);
        }
      }
    }
    return (f[n][m][0] + f[n][m][2]) % MOD;
  }
};
