#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 300000 + 10, M = 20;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
};

i64 cross(const Point &o, const Point &a, const Point &b) {
  return ((i64)a.x - o.x) * (b.y - o.y) - ((i64)a.y - o.y) * (b.x - o.x);
}

class EnclosingTriangle {
  int n, f[N];
  Point p[N];
  std::vector<Point> q;
  bool check(const Point &a, const Point &b) {
    for (int i = 0; i < q.size(); ++i) if (cross(a, b, q[i]) < 0) return false;
    return true;
  }
  i64 sum;
  int cnt, k, g[N];
  void add(int x, int y) {
    g[x] += y;
    if (x >= k) cnt += y, sum += (i64)x * y;
  }
  void inc() {
    cnt -= g[k];
    sum -= (i64)g[k] * k;
    ++k;
  }
 public:
  i64 getNumber(int m, vector<int> x, vector<int> y) {
    for (int i = 0; i < x.size(); ++i) q.push_back(Point(x[i], y[i]));
    n = 0;
    for (int i = 0; i < m; ++i) p[n++] = Point(i, 0);
    for (int i = 0; i < m; ++i) p[n++] = Point(m, i);
    for (int i = m; i > 0; --i) p[n++] = Point(i, m);
    for (int i = m; i > 0; --i) p[n++] = Point(0, i);
    // calculate f_i
    for (int i = 0, j = 0; i < n; ++i) {
      j = std::max(j, i);
      while (check(p[i], p[j % n])) ++j;
      f[i] = j - 1;
    }
    // count the number of tuples (i, j, k), s.t, f[i] >= j, f[j] >= k and f[k] >= i + n
    // sum of max(f[j] - k + 1, 0)
    i64 res = 0;
    sum = cnt = k = 0;
    memset(g, 0, sizeof g);
    for (int i = 0, j = 0; i < n; ++i) {
      // j and k are both moitonous
      for (; j < n && j <= f[i]; ++j) add(std::min(f[j], n - 1), 1), add(j, -1);
      while (k < n && f[k] < i + n) inc();
      add(std::min(f[i], n - 1), -1);
      add(i, 1);
      res += sum - (k - 1LL) * cnt;
    }
    return res;
  }
};
