#include <bits/stdc++.h>

using namespace std;

class TwoConvexShapes {
  static const int N = 50 + 10, MOD = 1000000007;
  int n, m;
  std::vector<std::string> s;
  int dispatch(char c) {
    switch (c) {
      case 'B': return 1;
      case 'W': return 2;
      default: return 0;
    }
  }
  int solve() {
    static int f[N][N]; // number of ways
    memset(f, 0, sizeof f);
    f[0][m] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = m; j >= 0; --j) f[i + 1][j] = (f[i][j] + f[i + 1][j + 1]) % MOD;
      int a = -1, b = m;
      for (int j = 0; j < m; ++j) if (s[i][j] == 1) a = j;
      for (int j = m - 1; j >= 0; --j) if (s[i][j] == 2) b = j;
      for (int j = 0; j <= m; ++j) if (b < j || a >= j) f[i + 1][j] = false;
    }
    int res = 0;
    for (int i = 0; i <= m; ++i) (res += f[n][i]) %= MOD;
    return res;
  }
 public:
  int countWays(vector<string> _s) {
    s = _s;
    n = s.size(), m = s[0].length();
    int cnt[3] = {0, 0, 0};
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        ++cnt[s[i][j] = dispatch(s[i][j])];
    // top left
    int res = solve();
    // top right
    for (int i = 0; i < n; ++i) std::reverse(s[i].begin(), s[i].end());
    (res += solve()) %= MOD;
    // bottom right
    std::reverse(s.begin(), s.end());
    (res += solve()) %= MOD;
    // bottom left
    for (int i = 0; i < n; ++i) std::reverse(s[i].begin(), s[i].end());
    (res += solve()) %= MOD;
    static int pre[N], suf[N];
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i];
      for (int j = 0; j < m; ++j) pre[i + 1] |= 1 << s[i][j];
    }
    suf[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      suf[i] = suf[i + 1];
      for (int j = 0; j < m; ++j) suf[i] |= 1 << s[i][j];
    }
    // subtract the repeats
    for (int i = 1; i < n; ++i) {
      if (!(pre[i] & 2) && !(suf[i] & 4)) --res;
      if (!(pre[i] & 4) && !(suf[i] & 2)) --res;
    }
    for (int i = 0; i < m; ++i) {
      pre[i + 1] = pre[i];
      for (int j = 0; j < n; ++j) pre[i + 1] |= 1 << s[j][i];
    }
    suf[m] = 0;
    for (int i = m - 1; i >= 0; --i) {
      suf[i] = suf[i + 1];
      for (int j = 0; j < n; ++j) suf[i] |= 1 << s[j][i];
    }
    for (int i = 1; i < m; ++i) {
      if (!(pre[i] & 2) && !(suf[i] & 4)) --res;
      if (!(pre[i] & 4) && !(suf[i] & 2)) --res;
    }
    if (!cnt[1]) res -= 3;
    if (!cnt[2]) res -= 3;
    return (res + MOD) % MOD;
  }
};
