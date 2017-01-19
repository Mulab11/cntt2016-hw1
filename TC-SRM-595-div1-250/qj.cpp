#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class LittleElephantAndIntervalsDiv1 {
 public:
  i64 getNumber(int m, vector<int> l, vector<int> r) {
    // Every time we paint an interval [l, r], we use a new color to paint it.
    // Finally we decide what the colors exactly are.
    std::vector<int> col(m);
    int n = 0;
    for (int i = 0; i < l.size(); ++i) {
      ++n;
      for (int j = l[i] - 1; j < r[i]; ++j) col[j] = n;
    }
    std::sort(col.begin(), col.end());
    i64 res = 1;
    for (int t = std::unique(col.begin(), col.end()) - col.begin(); t--;) res *= 2;
    if (col[0] == 0) res /= 2;
    return res;
  }
};
