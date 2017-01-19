#include <bits/stdc++.h>

using namespace std;

typedef std::pair<std::string, std::string> Info;

const int N = 50 + 10;
const Info INF(std::string(N, '9'), std::string(N, '9'));

class LeftRightDigitsGame2 {
  int n;
  Info f[N][N][2][2];
  std::string s, t;
  template <typename T> inline void check(T &lhs, const T &rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  string minNumber(string _s, string _t) {
    s = _s, t = _t;
    n = s.length();
    std::reverse(s.begin(), s.end());
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n; ++j)
        for (int x = 0; x < 2; ++x)
          for (int y = 0; y < 2; ++y)
            f[i][j][x][y] = INF; // memorize a way when doing DP
    f[0][0][0][0] = Info("", "");
    // then DP
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
        const int k = n - 1 - (i - j);
        for (int x = 0; x < 2; ++x) {
          for (int y = 0; y < 2; ++y) {
            const Info &cur = f[i][j][x][y];
            if (cur == INF) continue;
            Info info(cur.first, s[i] + cur.second);
            int q = (s[i] < t[k]) || (s[i] == t[k] && y);
            check(f[i + 1][j][x][q], info);
            if (!x && s[i] < t[j]) continue;
            info = Info(cur.first + s[i], cur.second);
            int p = x || (s[i] > t[j]);
            check(f[i + 1][j + 1][p][y], info);
          }
        }
      }
    }
    std::string res = INF.first;
    for (int i = 0; i <= n; ++i) {
      for (int x = 0; x < 2; ++x) {
        for (int y = 0; y <= x; ++y) {
          const Info &cur = f[n][i][x][y];
          if (cur == INF) continue;
          // combine the left side and the right side
          check(res, cur.first + cur.second);
        }
      }
    }
    return res == INF.first ? "" : res;
  }
};
