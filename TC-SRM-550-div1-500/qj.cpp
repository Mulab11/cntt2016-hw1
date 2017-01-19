#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class CheckerExpansion {
 public:
  vector<string> resultAfter(i64 t, i64 x0, i64 y0, int w, int h) {
    std::vector<std::string> res(h, std::string(w, 0));
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        i64 x = x0 + j, y = y0 + h - i - 1, p = (x + y) / 2, q = (x - y) / 2;
        if (((x + y) & 1) || p >= t || y > x || (~p & q)) {
          res[i][j] = '.';
          continue;
        }
        res[i][j] = (((x + y) / 2) & 1) + 'A';
      }
    }
    return res;
  }
};
