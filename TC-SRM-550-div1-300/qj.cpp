#include <bits/stdc++.h>

using namespace std;

typedef std::pair<int, int> Info;

class RotatingBot {
  static const int N = 50 + 10;
 public:
  int minArea(vector<int> a) {
    const int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};
    std::set<Info> pool;
    int x = 0, y = 0;
    pool.insert(Info(x, y));
    for (int i = 0; i < a.size(); ++i) {
      int k = i % 4;
      for (int j = a[i]; j--;) if (!pool.insert(Info(x += dx[k], y += dy[k])).second) return -1;
    }
    int l = 0, r = 0, u = 0, d = 0;
    for (std::set<Info>::iterator it = pool.begin(); it != pool.end(); ++it) {
      int x = it->first, y = it->second;
      l = std::min(l, y);
      r = std::max(r, y);
      d = std::min(d, x);
      u = std::max(u, x);
    }
    // get the border
    x = y = 0;
    pool.clear();
    pool.insert(Info(0, 0));
    for (int i = 0; i < a.size(); ++i) {
      int k = i % 4;
      for (int j = a[i]; j--;) pool.insert(Info(x += dx[k], y += dy[k]));
      int p = x + dx[k], q = y + dy[k];
      if (i + 1 < a.size() && d <= p && p <= u && l <= q && q <= r && !pool.count(Info(p, q))) return -1;
    }
    return (r - l + 1) * (u - d + 1);
  }
};
