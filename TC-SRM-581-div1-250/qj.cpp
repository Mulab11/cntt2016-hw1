#include <bits/stdc++.h>

using namespace std;

class SurveillanceSystem {
 public:
  string getContainerInfo(string s, vector<int> a, int m) {
    const int n = s.length();
    std::vector<int> x(m + 1), y(m + 1);
    for (int i = 0; i < a.size(); ++i) ++x[a[i]];
    for (int i = 0; i + m <= n; ++i) ++y[std::count(s.begin() + i, s.begin() + i + m, 'X')];
    std::string res;
    for (int i = 0; i < n; ++i) {
      bool p = false;
      for (int j = std::max(i - m + 1, 0); j <= i && j + m <= n; ++j) {
        int t = std::count(s.begin() + j, s.begin() + j + m, 'X');
        if (x[t]) p = true; // possible to be monitored
      }
      for (int j = std::max(i - m + 1, 0); j <= i && j + m <= n; ++j) {
        int t = std::count(s.begin() + j, s.begin() + j + m, 'X');
        --y[t];
      }
      bool q = true;
      for (int j = 0; j <= m; ++j) if (x[j] > y[j]) q = false; // impossible not to be monitored
      for (int j = std::max(i - m + 1, 0); j <= i && j + m <= n; ++j) {
        int t = std::count(s.begin() + j, s.begin() + j + m, 'X');
        ++y[t];
      }
      if (p && q) res += '?'; else if (p) res += '+'; else res += '-';
    }
    return res;
  }
};
