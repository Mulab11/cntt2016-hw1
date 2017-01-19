#include <bits/stdc++.h>

using namespace std;

class TheTree {
 public:
  int maximumDiameter(vector<int> cnt) {
    int d = cnt.size();
    cnt.insert(cnt.begin(), 1);
    int res = 0;
    for (int i = 0; i <= d; ++i) {
      // enumerate the depth of LCA
      int cur = d - i; // the distance of one of the leaves from LCA
      for (int j = i + 1; j <= d; ++j) if (cnt[j] > 1) ++cur; else break; // maximize the depth of another leaf
      res = std::max(res, cur);
    }
    return res;
  }
};
