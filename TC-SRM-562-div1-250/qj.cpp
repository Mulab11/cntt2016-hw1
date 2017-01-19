#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class PastingPaintingDivOne {
  int dispatch(char ch) {
    switch (ch) {
      case 'R': return 0;
      case 'G': return 1;
      case 'B': return 2;
      case '.': return 3;
    }
  }
  std::vector<i64> res;
  void solve(const std::string &s, int t) {
    for (int i = 0, l = 0; i < s.length(); ++i) {
      int c = dispatch(s[i]);
      if (c < 3) {
        res[c] += i + t - std::max(l, i);
        l = std::max(l, i + t);
      }
    }
  }
 public:
  vector<i64> countColors(vector<string> s, int t) {
    const int n = s.size(), m = s[0].length();
    std::vector<std::string> a(n + m + 1);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        a[i - j + m].push_back(s[i][j]);
    res.resize(4);
    for (int i = 0; i <= n + m; ++i) solve(a[i], t); // find the pattern
    res.resize(3);
    return res;
  }
};
