#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int T = 233333;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
  inline bool operator== (const Point &rhs) const { return x == rhs.x && y == rhs.y; }
};

i64 cross(const Point &o, const Point &a, const Point &b) {
  return ((i64)a.x - o.x) * (b.y - o.y) - ((i64)a.y - o.y) * (b.x - o.x);
}

class ConvexPolygonGame {
  int n;
  std::vector<Point> p;
 public:
  string winner(vector<int> x, vector<int> y) {
    // It's obvious that if we can draw a small triangle, then we win.
    // So our problem is to detect if there exists three points which are not collinear.
    // As |x_i|, |y_i| <= 100000, if the polygon contains more than 200000 points, there must exist three non-collinear points, otherwise we could enumerate all points to check if p_1, p_2 and p_i are collinear.
    n = x.size();
    for (int i = 0; i < n; ++i) p.push_back(Point(x[i], y[i]));
    p.push_back(p[0]);
    std::vector<Point> pool;
    int l = *std::min_element(x.begin(), x.end()), r = *std::max_element(x.begin(), x.end());
    for (int i = l; i <= r; ++i) {
      int d, u;
      for (int j = 0; j < n; ++j) {
        if (std::min(p[j].x, p[j + 1].x) <= i && i <= std::max(p[j].x, p[j + 1].x)) {
          if (p[j].x == p[j + 1].x) continue;
          i64 a = (i64)(p[j + 1].y - p[j].y) * (i - p[j].x), b = p[j + 1].x - p[j].x;
          a += (i64)p[j].y * b;
          if (b < 0) a = -a, b = -b;
          if (p[j].x < p[j + 1].x) {
            if (a > 0) d = (a + b - 1) / b; else d = a / b;
            if (Point(i, d) == p[j] || Point(i, d) == p[j + 1]) ++d;
          } else {
            if (a > 0) u = a / b; else u = (a - b + 1) / b;
            if (Point(i, u) == p[j] || Point(i, u) == p[j + 1]) --u;
          }
        }
      }
      for (int j = d; j <= u; ++j) pool.push_back(Point(i, j));
      if (pool.size() > T) return "Masha";
    }
    for (int i = 2; i < pool.size(); ++i) if (cross(pool[0], pool[1], pool[i])) return "Masha";
    return "Petya";
  }
};
