#include <bits/stdc++.h>

using namespace std;

class BinPacking {
  int greedy(std::vector<int> a) {
    // use greedy method to match the remaining items
    std::sort(a.rbegin(), a.rend());
    int res = 0;
    for (int i = 0; i < a.size(); ++i) {
      if (i + 1 != a.size() && a.back() + a[i] <= 300) a.pop_back();
      ++res;
    }
    return res;
  }
 public:
  int minBins(vector<int> a) {
    int res = a.size(), cnt = 0;
    for (int i = 0; i < a.size(); ++i) if (a[i] == 100) ++cnt;
    // enumrate the number of disks that contains three 100-size items.
    for (int i = 0;;) {
      res = std::min(res, greedy(a) + i);
      if (3 * ++i > cnt) break;
      for (int j = 3; j--;) a.erase(std::find(a.begin(), a.end(), 100));
    }
    return res;
  }
};
