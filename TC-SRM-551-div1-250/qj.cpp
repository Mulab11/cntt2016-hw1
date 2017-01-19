#include <bits/stdc++.h>

using namespace std;

class ColorfulChocolates {
 public:
  int maximumSpread(string s, int m) {
    const int n = s.length();
    int res = 1;
    for (int i = 0; i < n; ++i) {
      std::vector<int> pool;
      for (int j = i - 1, k = i - 1; j >= 0; --j) if (s[j] == s[i]) pool.push_back(k-- - j);
      for (int j = i + 1, k = i + 1; j < n; ++j) if (s[j] == s[i]) pool.push_back(j - k++);
      std::sort(pool.begin(), pool.end());
      int cur = 1;
      for (int j = 0, k = m; j < pool.size(); ++j) if ((k -= pool[j]) >= 0) ++cur; else break;
      res = std::max(res, cur);
    }
    return res;
  }
};
