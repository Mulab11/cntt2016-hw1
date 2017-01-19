#include <bits/stdc++.h>

using namespace std;

class BoundedOptimization {
  static const int N = 13;
  int adj[N];
 public:
  double maxValue(vector<string> expr, vector<int> l, vector<int> r, int m) {
    std::string e;
    for (int i = 0; i < expr.size(); ++i) e += expr[i];
    memset(adj, 0, sizeof adj);
    for (int i = 0; i < e.length(); i += 3) {
      int a = e[i] - 'a', b = e[i + 1] - 'a';
      if (a < b) std::swap(a, b);
      adj[a] |= 1 << b;
    }
    const int n = l.size();
    double res = 0.;
    for (int s = 0; s < (1 << n); ++s) {
      for (int x = s;; x = (x - 1) & s) {
        // x : lower bound
        // y = s - x: upper bound
        // ~s : unbounded
        static double a[N], b[N];
        int sum = m;
        for (int i = 0; i < n; ++i) if (s >> i & 1) sum -= (a[i] = ((x >> i & 1) ? l[i] : r[i])); else a[i] = 0.;
        bool flag = true;
        if (sum < 0) flag = false;
        memset(b, 0, sizeof b);
        double cur = 0.;
        for (int i = 0; i < n; ++i) {
          bool u = s >> i & 1;
          for (int j = 0; j < i; ++j) {
            bool v = s >> j & 1;
            if (!u && !v) {
              if (!(adj[i] >> j & 1)) flag = false;
              continue;
            }
            if (!(adj[i] >> j & 1)) continue;
            if (u == v) cur += a[i] * a[j]; else if (u) b[j] += a[i]; else b[i] += a[j];
          }
        }
        int cnt = 0;
        double c = sum;
        for (int i = 0; i < n; ++i) if (!(s >> i & 1)) ++cnt, c -= b[i];
        c /= cnt;
        for (int i = 0; i < n; ++i) {
          if (s >> i & 1) continue;
          double z = b[i] + c;
          if (!(l[i] <= z && z <= r[i])) flag = false;
          cur += z * (b[i] + (sum - z) / 2.);
        }
        if (flag) res = std::max(res, cur);
        if (!x) break;
      }
    }
    return res;
  }
};
