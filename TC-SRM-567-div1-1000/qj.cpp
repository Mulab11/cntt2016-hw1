#include <bits/stdc++.h>

using namespace std;

class Mountains {
  static const int MOD = 1000000009;
  int n, m;
  std::vector<int> h;
  std::vector<std::string> a;
  std::map<std::string, int> mem[10];
  int dfs(int i, const std::string &cur) {
    if (i < 0) return 1;
    // cur : current height of each column
    if (mem[i].count(cur)) return mem[i][cur];
    int res = 0;
    for (int j = 0; j < m; ++j) {
      bool flag = true;
      for (int k = 0; k < m; ++k) if ((a[i][k] == 'X') != (h[i] - abs(k - j) > cur[k])) flag = false;
      if (!flag) continue;
      std::string temp = cur;
      for (int k = 0; k < m; ++k) {
        temp[k] = std::max<int>(temp[k], h[i] - abs(k - j));
        temp[k] = std::max<int>(temp[k], h[i] - abs(k - j));
      }
      (res += dfs(i - 1, temp)) %= MOD;
    }
    return mem[i][cur] = res;
  }
 public:
  int countPlacements(vector<int> _h, vector<string> _a) {
    a = _a, h = _h;
    n = a.size();
    return dfs(n - 1, std::string(m = a[0].length(), 0));
  }
};
