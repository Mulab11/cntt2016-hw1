#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class AlternateColors2 {
 public:
  i64 countWays(int n, int k) {
    i64 res = 0;
    for (int i = 0; 3 * i <= n; ++i) {
      // i = min(r, g, b)
      if (3 * i >= k) {
        if (k % 3 == 1) {
          int m = n - 3 * i;
          res += (m + 2LL) * (m + 1) / 2; // C(m + 2, 2)
        }
        break;
      }
      int x = n - 3 * i, y = k - 3 * i;
      // 2 * min(r, g) >= y
      // 2 * r >= y, 2 * (x - r) >= y  <==>  2 * r <= 2 * x - y
      // y <= 2 * r <= 2 * x - y
      int l = (y + 1) / 2, r = std::min(x, (2 * x - y) / 2);
      if (y & 1) res += 2 * std::max(r - l + 1, 0);
      // r >= x - r, 2 * (x - r) < y
      // x <= 2 * r
      // 2 * r > 2 * x - y
      // r <= x
      l = std::max((2 * x - y) / 2 + 1, (x + 1) / 2);
      r = x;
      if (l <= r) res += 2 * (r - l) + 1;
    }
    return res;
  }
};
