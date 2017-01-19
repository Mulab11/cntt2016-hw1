#include <bits/stdc++.h>

using namespace std;

class TriangleXor {
  int w;
  inline double x(int i) { return i ? 1. / (1. / w + 1. / i) : 0.; }
  inline double y(int i) { return x(i) / w; }
 public:
  int theArea(int _w) {
    w = _w;
    double res = 0.;
    for (int i = 1; i <= w; i += 2) {
      //y = x / w
      //y = 1 - x / i
      //x / w = 1 - x / i
      //x / w + x / i = 1
      res += x(i) - x(i - 1);
      res += (w - 2. * x(i)) * (y(i + 1) - y(i - 1)) / 2.;
    }
    if (!(w & 1)) res += w / 4.;
    return res;
  }
};
