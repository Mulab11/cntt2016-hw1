#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 233, MOD = 100007;
const double eps = 1e-12, PI = acos(-1.);

class FencingPenguins {
  struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y): x(_x), y(_y) {}
  };
  inline double cross(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
  }
  int sgn(double x) {
    if (fabs(x) < eps) return 0;
    return x > 0. ? 1 : -1;
  }
  int n, m;
  std::string z;
  int f[N][N], g[N][N], h[N][N][2];
  i64 id[N][N], mask[N][N];
  bool flag[N][N];
  std::vector<Point> p, q;
  void solve(const Point &s, const Point &t, i64 &x, i64 &y) {
    // calculate the points on s->t 's left side and the colors on its left side
    x = y = 0;
    for (int i = 0; i < m; ++i) if (sgn(cross(s, t, p[i])) <= 0) x |= 1LL << i, y |= 1LL << z[i];
  }
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
 public:
  int countWays(int _n, int _r, vector<int> x, vector<int> y, string _z) {
    n = _n, z = _z;
    m = x.size();
    for (int i = 0; i < m; ++i) p.push_back(Point(x[i], y[i])), z[i] = isupper(z[i]) ? (z[i] - 'A') : (z[i] - 'a' + 26);
    for (int i = 0; i < n; ++i) q.push_back(Point(_r * cos(2. * PI * i / n), _r * sin(2. * PI * i / n)));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        solve(q[i], q[j], id[i][j], mask[i][j]);
    for (int i = 0; i < n - 1; ++i) if (id[i][i + 1]) return 0;
    if (id[n - 1][0]) return 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        flag[i][j] = !(mask[i][j] & mask[j][i]); // vector i->j is legal
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    memset(h, 0, sizeof h);
    for (int l = n - 1; l >= 0; --l) {
      for (int r = l; r < n; ++r) {
        if (l == r) {
          h[l][r][1] = 1;
          continue;
        }
        for (int s = 0; s < 2; ++s) {
          for (int i = l + 1; i <= r; ++i) {
            if (!flag[l][i]) continue;
            int t = s || (id[l][r] & id[i][l] & id[r][i]);
            int cur = h[i][r][t];
            if (!id[l][i]) add(h[l][r][s], cur); else if (!(id[l][i] & id[i - 1][l + 1])) add(h[l][r][s], (i64)cur * f[l + 1][i - 1]);
          }
        }
        for (int i = l + 2; i <= r; ++i) {
          if (!flag[l][i]) continue;
          i64 t = id[i][l] & id[l][r];
          int cur = h[l][i][0];
          if (!t) add(g[l][r], cur); else if (!(t & id[r][i + 1])) add(g[l][r], (i64)cur * f[i + 1][r]);
        }
        for (int i = l; i <= r; ++i) if (!(id[l][r] & id[r][i])) add(f[l][r], g[i][r]);
      }
    }
    return f[0][n - 1];
  }
};
