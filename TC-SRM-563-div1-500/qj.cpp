#include <bits/stdc++.h>

using namespace std;

class SpellCards {
  static const int INF = 0x3f3f3f3f;
 public:
  int maxDamage(vector<int> a, vector<int> b) {
    // just become a knapsack problem
    const int n = a.size();
    std::vector<int> f(n + 1, -INF);
    f[0] = 0;
    for (int i = 0; i < n; ++i)
      for (int j = n; j >= a[i]; --j)
        f[j] = std::max(f[j], f[j - a[i]] + b[i]);
    return *std::max_element(f.begin(), f.end());
  }
};
