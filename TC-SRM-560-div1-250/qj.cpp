#include <bits/stdc++.h>

using namespace std;

class TomekPhone {
 public:
  int minKeystrokes(vector<int> a, vector<int> b) {
    std::sort(a.rbegin(), a.rend());
    std::vector<int> c;
    for (int i = 0; i < b.size(); ++i)
      for (int j = 1; j <= b[i]; ++j)
        c.push_back(j);
    std::sort(c.begin(), c.end());
    if (c.size() < a.size()) return -1;
    int res = 0;
    for (int i = 0; i < a.size(); ++i) res += a[i] * c[i]; // greedy
    return res;
  }
};
