#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int S = 60;

class XorCards {
  std::vector<i64> eq;
  int n;
  void insert(i64 x) {
    // gaussian elimination
    for (int i = 0; i < eq.size(); ++i) if ((x ^ eq[i]) < x) x ^= eq[i];
    if (x) eq.push_back(x);
  }
  i64 solve() {
    for (int i = 0; i < eq.size(); ++i) if (eq[i] == 1) return 0; // 0 = 1: illegal
    return 1LL << (n - eq.size());
  }
 public:
  i64 numberOfWays(vector<i64> a, i64 m) {
    n = a.size();
    ++m;
    i64 res = 0;
    for (int i = S - 1; i >= 0; --i) {
      if (!(m >> i & 1)) continue;
      // enumerate the first bit that our result differs from m
      eq.clear();
      for (int j = i; j < S; ++j) {
        i64 cur = 0;
        for (int k = 0; k < n; ++k) if (a[k] >> j & 1) cur |= 1LL << (k + 1);
        if (j > i && (m >> j & 1)) cur |= 1; // bits higher than i must be equal to the corresponding bits of m
        insert(cur);
      }
      res += solve();
    }
    return res;
  }
};
