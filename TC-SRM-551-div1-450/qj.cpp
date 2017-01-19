#include <bits/stdc++.h>

using namespace std;

class ColorfulWolves {
  static const int N = 50 + 10, INF = 0x3f3f3f3f;
  int f[N][N];
 public:
  int getmin(vector<string> s) {
    const int n = s.size();
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++i) {
      f[i][i] = 0;
      for (int j = 0, k = 0; j < n; ++j) if (s[i][j] == 'Y') f[i][j] = k++;
    }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
    int res = f[0][n - 1];
    return res == INF ? -1 : res;
  }
};
