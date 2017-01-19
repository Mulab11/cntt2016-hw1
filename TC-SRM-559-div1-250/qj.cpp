#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class HyperKnight {
 public:
  i64 countCells(int a, int b, int n, int m, int k) {
    const int dx[] = {a, a, -a, -a, b, b, -b, -b};
    const int dy[] = {b, -b, b, -b, a, -a, a, -a};
    i64 f[9];
    memset(f, 0, sizeof f);
    for (int s = 0; s < (1 << 8); ++s) {
      int l = 0, r = n, p = 0, q = m;
      for (int i = 0; i < 8; ++i) {
        if (!(s >> i & 1)) continue;
        // 0 <= x + dx[i] < n
        // 0 <= y + dy[i] < m
        l = std::max(l, -dx[i]);
        r = std::min(r, n - dx[i]);
        p = std::max(p, -dy[i]);
        q = std::min(q, m - dy[i]);
      }
      if (l < r && p < q) f[__builtin_popcount(s)] += ((i64)r - l) * (q - p);
    }
    i64 fact[10];
    fact[0] = 1;
    for (int i = 1; i < 10; ++i) fact[i] = fact[i - 1] * i;
    for (int i = 8; i >= 0; --i)
      for (int j = i + 1; j < 9; ++j)
        f[i] -= f[j] * (fact[j] / fact[i] / fact[j - i]); // inclusive-exclusive principle
    return f[k];
  }
};
