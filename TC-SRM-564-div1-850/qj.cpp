#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class DefectiveAddition {
  static const int N = 50 + 10, MOD = 1000000007;
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
 public:
  int count(vector<int> a, int m) {
    const int n = a.size();
    std::sort(a.begin(), a.end());
    int res = 0;
    for (int i = 31;; --i) {
      if (i < 0) {
        ++res;
        break;
      }
      int cnt[2] = {0, 0};
      for (int j = 0; j < n; ++j) ++cnt[a[j] >> i & 1];
      if (!cnt[1] && (m >> i & 1)) break;
      int mask = (1 << i) - 1;
      static int f[N][2][2];
      memset(f, 0, sizeof f);
      f[0][0][0] = 1;
      for (int j = 0; j < n; ++j) {
        int b = a[j] & mask;
        for (int x = 0; x < 2; ++x) {
          for (int y = 0; y < 2; ++y) {
            // x : i-th bit
            // y : whether we have selected an unbounded element
            int cur = f[j][x][y];
            if (!cur) continue;
            if (a[j] >> i & 1) {
              if (!y) add(f[j + 1][x][1], cur); else add(f[j + 1][x][y], cur * (mask + 1LL));
              add(f[j + 1][!x][y], cur * (b + 1LL));
            } else {
              add(f[j + 1][x][y], cur * (b + 1LL));
            }
          }
        }
      }
      int t = m >> i & 1;
      add(res, f[n][t][1]);
      if ((cnt[1] & 1) != t) break;
    }
    return res;
  }
};
