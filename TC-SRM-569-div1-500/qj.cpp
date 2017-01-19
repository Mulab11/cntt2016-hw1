#include <bits/stdc++.h>

using namespace std;

class TheJediTest {
 public:
  int minimumSupervisors(vector<int> a, int k) {
    const int n = a.size();
    int res = 0;
    for (int i = 0, cur = 0; i < n; ++i) {
      int r = (a[i] + cur) % k;
      if (i + 1 < n && a[i] >= r) {
        res += (a[i] - r + cur) / k;
        cur = r;
      } else {
        int x = (a[i] + cur + k - 1) / k;
        int y = x * k - a[i] - cur;
        if (i + 1 < n) a[i + 1] = std::max(a[i + 1] - y, 0);
        res += x;
        cur = 0;
      }
    }
    return res;
  }
};
