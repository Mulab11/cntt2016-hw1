#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10;
const double eps = 1e-10, PI = acos(-1.);

class CircusTents {
  int n;
  struct Circle {
    int x, y;
    double z;
    Circle() {}
    Circle(int _x, int _y, double _z): x(_x), y(_y), z(_z) {}
  } c[N];
  inline double sqr(double x) { return x * x; }
  inline double dist(const Circle &a, const Circle &b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }
  bool check() {
    std::map<double, int> tag;
    tag[0] = 0;
    tag[2. * PI] = 0;
    for (int i = 1; i < n; ++i) {
      double d = dist(c[0], c[i]);
      if (d >= c[0].z + c[i].z) continue;
      double x = c[i].x - c[0].x, y = c[i].y - c[0].y;
      double a = fmod(atan2(y, x) + 2. * PI, 2. * PI), b = acos((sqr(c[0].z) + sqr(d) - sqr(c[i].z)) / 2. / d / c[0].z); // arg of the intersection
      if (d <= fabs(c[0].z - c[i].z)) b = 1. / 0.;
      double u = acos(c[0].z / d); // arg of the tangent point
      double v = sin(u) * d; // length of the tangent point
      double t = c[i].z - v;
      if (t >= 0.) b = std::min(b, u + t / c[0].z);
      if (b >= PI) return false;
      double l = a - b, r = a + b;
      if (l < 0.) {
        ++tag[l + 2. * PI];
        --tag[2. * PI];
        ++tag[0];
        --tag[r];
      } else if (r > 2. * PI) {
        ++tag[l];
        --tag[2. * PI];
        ++tag[0];
        --tag[r - 2. * PI];
      } else {
        ++tag[l];
        --tag[r];
      }
    }
    double p = 0.;
    int q = 0;
    for (std::map<double, int>::iterator it = tag.begin(); it != tag.end(); p = it->first, q += it->second, ++it)
      if ((it->first - p > eps) && !q) return true;
    return false;
  }
 public:
  double findMaximumDistance(vector<int> x, vector<int> y, vector<int> z) {
    n = x.size();
    double l = 0., r = 1e5;
    while (fabs(r - l) > eps) {
      double mid = (l + r) / 2.;
      for (int i = 1; i < n; ++i) c[i] = Circle(x[i], y[i], z[i] + mid);
      c[0] = Circle(x[0], y[0], z[0]);
      if (check()) l = mid; else r = mid;
    }
    return l;
  }
};
