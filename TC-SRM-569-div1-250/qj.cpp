#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class TheDevice {
 public:
  int minimumAdditional(vector<string> s) {
    const int n = s.size(), m = s[0].length();
    int res = 0;
    for (int i = 0; i < m; ++i) {
      int cnt[2] = {0, 0};
      for (int j = 0; j < n; ++j) ++cnt[s[j][i] - '0'];
      res = std::max(res, std::max(2 - cnt[1], 0) + std::max(1 - cnt[0], 0)); // greedy
    }
    return res;
  }
};
