#include <bits/stdc++.h>

using namespace std;

const int N = 300 + 10, INF = 0x3f3f3f3f;

class FlippingBitsDiv1 {
  std::string a;
  int n, m, tot, row[N], col[N], r[N], c[N], f[N][2];
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  int getmin(vector<string> pool, int _m) {
    m = _m;
    for (int i = 0; i < pool.size(); ++i) a += pool[i];
    n = a.length();
    tot = (n - 1) / m + 1;
    // treat a as a tot * m matrix
    // a_0 ... a_m-1
    // a_m ... a_2m-1
    // ...
    // a_(tot - 1)*m ... a_n
    // then the operation become to flip first k rows, and our target is to make every column the same
    int res = N;
    if (tot < m) {
      memset(col, 0, sizeof col);
      memset(c, 0, sizeof c);
      for (int i = 0; i < n; ++i) {
        int x = i / m, y = i % m;
        ++c[y];
        if (a[i] == '1') col[y] |= 1 << x;
      }
      for (int s = 0; s < (1 << tot); ++s) { // enumerate which row would be flipped
        int cur = __builtin_popcount(s ^ (s >> 1)); // mimimal cost
        for (int i = 0; i < m; ++i) {
          int t = __builtin_popcount((col[i] ^ s) & ((1 << c[i]) - 1));
          t = std::min(t, c[i] - t); // greedy
          cur += t;
        }
        check(res, cur);
      }
    } else {
      memset(row, 0, sizeof row);
      memset(r, 0, sizeof r);
      for (int i = 0; i < n; ++i) {
        int x = i / m, y = i % m;
        ++r[x];
        if (a[i] == '1') row[x] |= 1 << y;
      }
      for (int s = 0; s < (1 << m); ++s) { // enumerate what every row finally are
        for (int i = 0; i <= tot; ++i) f[i][0] = f[i][1] = INF;
        f[0][0] = f[0][1] = 0;
        for (int i = 0; i < tot; ++i) {
          for (int j = 0; j < 2; ++j) {
            check(f[i + 1][0], f[i][j] + (j != 0) + __builtin_popcount((row[i] ^ s) & ((1 << r[i]) - 1)));
            check(f[i + 1][1], f[i][j] + (j != 1) + __builtin_popcount((~row[i] ^ s) & ((1 << r[i]) - 1)));
          }
        }
        check(res, std::min(f[tot][0], f[tot][1] + 1));
      }
    }
    return res;
  }
};
