#include <bits/stdc++.h>

using namespace std;

const int N = 30;

class History {
  int n, dist[N][N];
  std::vector<int> a[N];
  std::vector<std::string> b;
  template <typename T> void parse(const std::string &s, std::vector<T> &res) {
    // input parser
    std::stringstream ss(s);
    for (T x; ss >> x;) res.push_back(x);
  }
  std::string concat(const std::vector<std::string> &s) {
    std::string res;
    for (int i = 0; i < s.size(); ++i) res += s[i];
    return res;
  }
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  string verifyClaims(vector<string> _a, vector<string> _b, vector<string> c) {
    n = _a.size();
    for (int i = 0; i < n; ++i) parse(_a[i], a[i]);
    parse(concat(_b), b);
    std::string res;
    for (int p = 0; p < c.size(); ++p) {
      memset(dist, 0x3f, sizeof dist);
      for (int i = 0; i < n; ++i) dist[i][i] = 0;
      b.push_back(c[p]);
      for (int i = 0; i < b.size(); ++i) {
        int x = b[i][0] - 'A', y = b[i][3] - 'A';
        int l = b[i][1] - '0', p = b[i][4] - '0';
        int r = a[x][l + 1] - 1, q = a[y][p + 1] - 1;
        l = a[x][l], p = a[y][p];
        //r + d_1 >= p + d_2
        //l + d_1 <= q + d_2
        //d_2 - d_1 >= l - q
        //d_1 - d_2 <= q - l
        //d_2 - d_1 <= r - p
        check(dist[x][y], r - p);
        check(dist[y][x], q - l);
      }
      b.pop_back();
      bool flag = true;
      // use floyd to solve the system of difference constraints
      for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            check(dist[i][j], dist[i][k] + dist[k][j]);
        for (int i = 0; i < n; ++i) {
          if (dist[i][i] < 0) {
            // check if illegal
            flag = false;
            break;
          }
        }
      }
      if (flag) res += 'Y'; else res += 'N';
    }
    return res;
  }
};
