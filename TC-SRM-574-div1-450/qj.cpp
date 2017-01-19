#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class PolygonTraversal {
  static const int N = 18;
  i64 f[1 << N][N];
 public:
  i64 count(int n, vector<int> p) {
    memset(f, 0, sizeof f);
    int mask = 0;
    for (int i = 0; i < p.size(); ++i) mask |= 1 << --p[i];
    f[mask][p.back()] = 1;
    for (int s = mask; s < (1 << n); ++s) {
      for (int i = 0; i < n; ++i) {
        i64 cur = f[s][i];
        // f[s][i]: the set of points we have visited is s, the last point is i
        if (!cur) continue;
        int t = s; // bitmask of banned points
        int l = i - 1;
        for (; !(s >> ((l + n) % n) & 1); --l) t |= 1 << ((l + n) % n);
        int r = i + 1;
        for (; !(s >> (r % n) & 1); ++r) t |= 1 << (r % n);
        for (int j = 0; j < n; ++j) if (!(t >> j & 1)) f[s | (1 << j)][j] += cur;
      }
    }
    mask = (1 << n) - 1;
    i64 res = 0;
    for (int i = 0; i < n; ++i) if (i != (p[0] + n - 1) % n && i != (p[0] + 1) % n) res += f[mask][i];
    return res;
  }
};
