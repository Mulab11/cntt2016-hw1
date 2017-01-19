#include <bits/stdc++.h>

using namespace std;

class IncrementAndDoubling {
 public:
  int getMin(vector<int> a) {
    // greedy
    int ans = 0;
    for (int i = 0; i < a.size(); ++i) if (a[i]) ans = std::max(ans, 31 - __builtin_clz(a[i]));
    for (int i = 0; i < a.size(); ++i) ans += __builtin_popcount(a[i]);
    return ans;
  }
};
