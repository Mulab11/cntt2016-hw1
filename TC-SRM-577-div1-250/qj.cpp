#include <bits/stdc++.h>

using namespace std;

class EllysRoomAssignmentsDiv1 {
  std::vector<int> a;
  void parse(const std::vector<std::string> &pool) {
    std::string s;
    for (int i = 0; i < pool.size(); ++i) s += pool[i];
    std::stringstream ss(s);
    a.clear();
    for (int x; ss >> x;) a.push_back(x);
  }
 public:
  double getAverage(vector<string> s) {
    parse(s);
    const int n = a.size(), b = a[0], m = (n + 19) / 20, r = (n + m - 1) / m;
    std::sort(a.rbegin(), a.rend());
    const int p = std::find(a.begin(), a.end(), b) - a.begin();
    std::vector<int> sum(n);
    for (int i = 0; i < n; ++i) sum[i / m] += a[i];
    while (!sum.back()) sum.pop_back();
    int y = n % m;
    if (!y) y = m;
    double x = (double)y / m;
    // just follow the problem
    // easy to fst...
    if (p / m + 1 < sum.size()) {
      double z = 0;
      for (int i = 0; i + 1 < sum.size(); ++i) if (i != p / m) z += sum[i];
      z /= m;
      z += b;
      return x * (z + (double)sum.back() / y) / r + (1. - x) * z / (r - 1.);
    } else {
      double z = 0.;
      for (int i = 0; i + 1 < sum.size(); ++i) z += sum[i];
      z /= m;
      z += b;
      return z / r;
    }
  }
};
