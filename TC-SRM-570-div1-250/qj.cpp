#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class RobotHerb {
  void solve(int op, int v, i64 &x, i64 &y) {
    if (op == 0)
      y += v;
    else if (op == 1)
      x += v;
    else if (op == 2)
      y -= v;
    else
      x -= v;
  }
 public:
  i64 getdist(int t, vector<int> a) {
    i64 x = 0, y = 0, z = (i64)t * a.size();
    std::vector<int> b;
    for (int i = 4; i--;) std::copy(a.begin(), a.end(), std::back_inserter(b));
    i64 p = z / b.size();
    int q = z % b.size();
    // just simulate the process
    for (int i = 0, d = 0; i < b.size(); d = (d + b[i++]) % 4) solve(d, b[i], x, y);
    x *= p;
    y *= p;
    for (int i = 0, d = 0; i < q; d = (d + b[i++]) % 4) solve(d, b[i], x, y);
    return llabs(x) + llabs(y);
  }
};
