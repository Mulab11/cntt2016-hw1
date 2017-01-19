#include <bits/stdc++.h>

using namespace std;

class PiecewiseLinearFunction {
 public:
  int maximumSolutions(vector<int> y) {
    // be cautious with the corner cases !
    for (int i = 0; i + 1 < y.size(); ++i) if (y[i] == y[i + 1]) return -1;
    int res = 0;
    for (int i = 0; i < y.size(); ++i) {
      for (int k = -1; k <= 1; ++k) {
        double cur = y[i] + .5 * k;
        int cnt = 0;
        for (int j = 0; j + 1 < y.size(); ++j) if (std::min(y[j], y[j + 1]) <= cur && cur <= std::max(y[j], y[j + 1])) ++cnt;
        for (int j = 1; j + 1 < y.size(); ++j) if (y[j] == cur) --cnt;
        res = std::max(res, cnt);
      }
    }
    return res;
  }
};
