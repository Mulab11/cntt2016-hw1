#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, S = 26, INF = 0x3f3f3f3f;

class StringWeight {
  int f[N][S + 1][S + 1];
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
  int calc(int a, int n) {
    //a + (a + 1) + ... + (a + n - 1)
    return n * a + n * (n - 1) / 2;
  }
 public:
  int getMinimum(vector<int> l) {
    memset(f, 0x3f, sizeof f);
    f[0][0][0] = 0;
    const int n = l.size();
    for (int i = 0, sum = 0; i < n; sum += l[i++]) {
      for (int a = 0; a <= S; ++a) {
        for (int b = 0; a + b <= S; ++b) {
          //considering i-th string
          //already used a chars
          //currently using b chars
          int cur = f[i][a][b];
          if (cur == INF) continue;
          int c = S - a - b;
          for (int x = 0; x <= c; ++x) {
            //begin using x chars
            //x + b >= l[i]
            for (int y = 0; x + y <= c; ++y) {
              //begin & end y chars
              for (int z = 0; z <= b; ++z) {
                //end z chars
                if (x + y + z > l[i]) continue;
                if (x + y + b < std::min(l[i], 26)) continue;
                check(f[i + 1][a + y + z][b + x - z], cur + calc(0, z) + calc(1, x) + (b - z ? 0 : (l[i] - z - x - y)) + l[i] * (b - z));
              }
            }
          }
        }
      }
    }
    int res = INF;
    for (int i = 0; i <= S; ++i) check(res, f[n][i][0]);
    return res;
  }
};
