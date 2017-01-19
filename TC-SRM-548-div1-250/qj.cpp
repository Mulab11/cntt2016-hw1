#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class KingdomAndTrees {
  bool check(std::vector<int> h, int x) {
    for (int i = 0; i < h.size(); ++i) h[i] = std::min(std::max(h[i] - x, (i ? h[i - 1] : 0) + 1), h[i] + x);
    for (int i = 1; i < h.size(); ++i) if (h[i] <= h[i - 1]) return false;
    return true;
  }
 public:
  int minLevel(vector<int> h) {
    int l = 0, r = 1000000100;
    while (l < r) {
      int mid = (l + r) / 2;
      if (check(h, mid)) r = mid; else l = mid + 1;
    }
    return l;
  }
};
