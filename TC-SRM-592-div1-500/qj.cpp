#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 50 + 10, MOD = 1000000007;

class LittleElephantAndPermutationDiv1 {
  int f[N][N][N * N];
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
 public:
  int getNumber(int n, int m) {
    memset(f, 0, sizeof f);
    f[n][0][0] = 1;
    for (int i = n; i > 0; --i) {
      for (int j = 0; j <= n - i; ++j) {
        // there are j unmatched slots
        for (int k = 0; k <= n * n; ++k) {
          // the magic value is k
          int cur = f[i][j][k];
          if (!cur) continue;
          int b = n - i - j, a = n - j - 2 * b;
          //0 - 0, not matched
          add(f[i - 1][j][k + 2 * i], a * (a - 1LL) * cur);
          //0 - 0, matched
          add(f[i - 1][j + 1][k + i], (i64)a * cur);
          //0 - 1 / 1 - 0
          add(f[i - 1][j + 1][k + i], 2LL * a * b * cur);
          //1 - 1
          add(f[i - 1][j + 2][k], (i64)b * b * cur);
        }
      }
    }
    int res = 0;
    for (int i = m; i <= n * n; ++i) add(res, f[0][n][i]);
    return res;
  }
};
