#include <bits/stdc++.h>

using namespace std;

class Incubator {
  static const int N = 50 + 10;
  std::vector<std::string> s;
  int n, match[N];
  bool flag[N];
  bool dfs(int a) {
    if (flag[a]) return false;
    flag[a] = true;
    for (int b = 0; b < n; ++b) {
      if (s[a][b] == 'N') continue;
      if (match[b] == -1 || dfs(match[b])) return match[b] = a, true;
    }
    return false;
  }
 public:
  int maxMagicalGirls(vector<string> _s) {
    // Dilworth's theorem
    s = _s;
    n = s.size();
    // transisive closure
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (s[i][k] == 'Y' && s[k][j] == 'Y') s[i][j] = 'Y';
    // minimum chain cover of a DAG
    int res = 0;
    memset(match, -1, sizeof match);
    for (int i = 0; i < n; ++i) if (memset(flag, 0, sizeof flag), dfs(i)) ++res;
    return n - res;
  }
};
