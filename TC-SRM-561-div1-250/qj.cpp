#include <bits/stdc++.h>

using namespace std;

class ICPCBalloons {
  static const int INF = 0x3f3f3f3f;
 public:
  int minRepaintings(vector<int> c, string s, vector<int> a) {
    if (std::accumulate(c.begin(), c.end(), 0) < std::accumulate(a.begin(), a.end(), 0)) return -1;
    std::vector<int> p[2];
    const int n = c.size(), m = a.size();
    for (int i = 0; i < n; ++i) p[s[i] == 'L'].push_back(c[i]);
    std::sort(p[0].rbegin(), p[0].rend());
    std::sort(p[1].rbegin(), p[1].rend());
    std::sort(a.rbegin(), a.rend());
    int res = INF;
    for (int s = 0; s < (1 << m); ++s) {
      std::vector<int> q[2];
      for (int i = 0; i < m; ++i) q[s >> i & 1].push_back(a[i]);
      int val = 0;
      for (int i = 0; i < 2; ++i) {
        if (std::accumulate(p[i].begin(), p[i].end(), 0) < std::accumulate(q[i].begin(), q[i].end(), 0)) {
          val = INF;
          break;
        }
        for (int j = 0; j < q[i].size(); ++j) val += std::max(q[i][j] - (j < p[i].size() ? p[i][j] : 0), 0);
      }
      res = std::min(res, val);
    }
    return res == INF ? -1 : res;
  }
};
