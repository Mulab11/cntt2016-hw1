#include <bits/stdc++.h>

using namespace std;

class MagicalHats {
  static const int N = 13, M = 1600000, INF = 0x3f3f3f3f;
  int id[N][N];
  int row[N], col[N], mask[1 << N], cnt[1 << N];
  int f[M];
  bool g[M];
 public:
  int findMaximumReward(vector<string> a, vector<int> c, int k) {
    std::sort(c.begin(), c.end());
    cnt[0] = 0;
    for (int i = 1; i < (1 << N); ++i) cnt[i] = cnt[i >> 1] + (i & 1);
    mask[0] = 0;
    for (int i = 0; i < (1 << N); ++i) mask[i] = 3 * mask[i >> 1] + (i & 1);
    const int n = a.size(), m = a[0].length();
    int tot = 0;
    memset(id, -1, sizeof id);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (a[i][j] == 'H') id[i][j] = tot, row[i] |= 1 << tot, col[j] |= 1 << tot, ++tot;
    memset(g, 0, sizeof g);
    for (int s = 0; s < (1 << tot); ++s) {
      if (cnt[s] != c.size()) continue;
      bool flag = true;
      for (int i = 0; i < n; ++i) if ((cnt[row[i]] + cnt[s & row[i]]) & 1) flag = false;
      for (int i = 0; i < m; ++i) if ((cnt[col[i]] + cnt[s & col[i]]) & 1) flag = false;
      if (flag) g[mask[(1 << tot) - 1] + mask[s]] = true;
    }
    for (int s = (1 << tot) - 1; s >= 0; --s) {
      for (int t = s; ~t; t = (t ? ((t - 1) & s) : -1)) {
        if (!g[mask[s] + mask[t]]) continue;
        for (int i = 0; i < tot; ++i) if (s >> i & 1) g[mask[s ^ (1 << i)] + mask[t & (s ^ (1 << i))]] = true;
      }
    }
    memset(f, -1, sizeof f);
    for (int s = (1 << tot) - 1; s >= 0; --s) {
      if (cnt[s] > k) continue;
      for (int t = s; ~t; t = (t ? ((t - 1) & s) : -1)) {
        int a = mask[s] + mask[t];
        if (!g[a]) continue;
        int &cur = f[a] = 0;
        if (cnt[s] == k) continue;
        for (int i = 0; i < tot; ++i) {
          if (s >> i & 1) continue;
          int b = mask[s ^ (1 << i)] + mask[t];
          int temp = INF;
          if (g[b]) temp = std::min(temp, f[b]);
          b = mask[s ^ (1 << i)] + mask[t ^ (1 << i)];
          if (g[b]) temp = std::min(temp, f[b] + c[cnt[t]]);
          cur = std::max(cur, temp);
        }
      }
    }
    return f[0];
  }
};
