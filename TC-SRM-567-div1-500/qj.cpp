#include <bits/stdc++.h>

using namespace std;

class StringGame {
  static const int N = 50 + 10;
  int mask[N];
  std::vector<int> t[N];
 public:
  vector<int> getWinningStrings(vector<string> s) {
    std::vector<int> res;
    const int n = s.size(), m = 26;
    for (int i = 0; i < n; ++i) {
      t[i].resize(m);
      for (int j = 0; j < s[i].length(); ++j) ++t[i][s[i][j] - 'a'];
    }
    for (int i = 0; i < n; ++i) {
      std::vector<bool> flag(n), mask(m);
      do {
     repeat: // iterate
        for (int j = 0; j < m; ++j) {
          if (mask[j]) continue;
          for (int k = 0; k < n; ++k) if (!flag[k] && t[k][j] > t[i][j]) goto fail; // if we choose j then s_i can't be the minimal string
          for (int k = 0; k < n; ++k) if (t[k][j] < t[i][j]) flag[k] = true; // these strings are greater than s_i
          mask[j] = true;
          goto repeat;
       fail:
          continue;
        }
      } while (0);
      if (std::count(flag.begin(), flag.end(), true) == n - 1) res.push_back(i); // all other strings are greater than s_i
    }
    return res;
  }
};
