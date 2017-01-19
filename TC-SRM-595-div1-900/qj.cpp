#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
};

inline int cross(const Point &a, const Point &b) {
  return a.x * b.y - a.y * b.x;
}

inline int cross(const Point &o, const Point &a, const Point &b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

class Constellation {
 public:
  double expectation(vector<int> x, vector<int> y, vector<int> prob) {
    const int n = x.size();
    std::vector<Point> p(n);
    for (int i = 0; i < n; ++i) p[i] = Point(x[i], y[i]);
    std::vector<double> q(n);
    for (int i = 0; i < n; ++i) q[i] = prob[i] / 1000.;
    double res = 0.;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        // Enumerate two points and calculate the probability that p_i and p_j are adjointing on the convex.
        if (i == j) continue;
        double cur = q[i] * q[j];
        for (int k = 0; k < n; ++k) {
          if (k == i || k == j) continue;
          int t = cross(p[i], p[j], p[k]);
          if (t == 0) {
            if (!(std::min(p[i].x, p[j].x) <= p[k].x && p[k].x <= std::max(p[i].x, p[j].x) &&
                  std::min(p[i].y, p[j].y) <= p[k].y && p[k].y <= std::max(p[i].y, p[j].y))) cur *= 1. - q[k];
          } else if (t < 0) {
            cur *= 1. - q[k];
          }
        }
        res += cross(p[i], p[j]) * cur;
      }
    }
    return res / 2.;
  }
};
