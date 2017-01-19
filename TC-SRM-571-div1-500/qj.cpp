#include <bits/stdc++.h>

using namespace std;

class MagicMolecule {
  int n, m;
  std::vector<std::string> a;
  std::vector<int> b, x, y;
  std::vector<bool> flag;
  int ans;
  void dfs(int i, int cnt = 0, int sum = 0) {
    if (sum <= ans) return;
    if (i == x.size()) {
      ans = sum;
      return;
    }
    int p = x[i], q = y[i];
    if (!flag[p] || !flag[q]) {
      // branching
      dfs(i + 1, cnt, sum);
      return;
    }
    if (cnt) {
      // we would only reach here n/3 times
      flag[p] = false;
      dfs(i + 1, cnt - 1, sum - b[p]);
      flag[p] = true;
      flag[q] = false;
      dfs(i + 1, cnt - 1, sum - b[q]);
      flag[q] = true;
    }
  }
 public:
  int maxMagicPower(vector<int> _b, vector<string> _a) {
    a = _a, b = _b;
    n = a.size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j)
        if (a[i][j] == 'N') x.push_back(i), y.push_back(j);
    m = 0;
    while (3 * m < 2 * n) ++m;
    flag.resize(n, true);
    ans = -1;
    dfs(0, n - m, std::accumulate(b.begin(), b.end(), 0));
    return ans;
  }
};
