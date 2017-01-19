#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class FoxPaintingBalls {
 public:
  i64 theMax(i64 r, i64 g, i64 b, int n) {
    if (n == 1) return r + g + b;
    if (r > g) std::swap(r, g);
    if (r > b) std::swap(r, b);
    if (g > b) std::swap(g, b);
    i64 tot = n * (n + 1LL) / 2, m = tot / 3;
    if (n % 3 == 1) {
      // m * x <= r
      // x <= r + g + b - 3 * m * x
      return std::min(r / m, (r + g + b) / (3 * m + 1));
    } else {
      return r / m;
    }
  }
};
