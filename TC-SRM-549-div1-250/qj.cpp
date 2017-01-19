#include <bits/stdc++.h>

using namespace std;

class PointyWizardHats {
 public:
  int getNumHats(vector<int> a1, vector<int> a2, vector<int> b1, vector<int> b2) {
    const int n = a1.size(), m = b1.size();
    std::vector< std::pair<double, int> > a, b;
    for (int i = 0; i < n; ++i) a.push_back(std::make_pair((double)a1[i] / a2[i], a2[i]));
    for (int i = 0; i < m; ++i) b.push_back(std::make_pair((double)b1[i] / b2[i], b2[i]));
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    int res = 0;
    std::multiset<int> pool;
    for (int i = 0, j = 0; i < n; ++i) {
      for (; j < m && b[j].first < a[i].first; ++j) pool.insert(b[j].second);
      std::multiset<int>::iterator it = pool.upper_bound(a[i].second);
      if (it != pool.end()) ++res, pool.erase(it);
    }
    return res;
  }
};
