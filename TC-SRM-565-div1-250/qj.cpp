#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class MonstersValley {
  static const int N = 100 + 10;
  i64 f[N];
  inline void check(i64 &lhs, i64 rhs) { if (rhs > lhs) lhs = rhs; }
 public:
  int minimumPrice(vector<i64> a, vector<int> b) {
    memset(f, 0, sizeof f);
    for (int i = 0; i < a.size(); ++i) {
      static i64 g[N];
      std::fill(g, g + N, -1);
      for (int j = 0; j < N; ++j) {
        if (f[j] >= a[i]) check(g[j], f[j]);
        if (f[j] >= 0 && j + b[i] < N) check(g[j + b[i]], f[j] + a[i]);
      }
      memcpy(f, g, sizeof g);
    }
    for (int i = 0;; ++i) if (f[i] >= 0) return i;
  }
};
