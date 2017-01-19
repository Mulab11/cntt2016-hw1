#include <bits/stdc++.h>

using namespace std;

class BallsSeparating {
  static const int INF = 0x3f3f3f3f;
 public:
  int minOperations(vector<int> r, vector<int> g, vector<int> b) {
    const int n = r.size();
    int res = INF;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (i == j || i == k || j == k) continue;
          // enumerate the final box
          int cur = r[j] + r[k] + g[i] + g[k] + b[i] + b[j];
          for (int p = 0; p < n; ++p) if (p != i && p != j && p != k) cur += std::min(std::min(r[p] + g[p], r[p] + b[p]), g[p] + b[p]);
          res = std::min(res, cur);
        }
      }
    }
    return res == INF ? -1 : res;
  }
};
