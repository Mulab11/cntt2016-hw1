#include <bits/stdc++.h>

using namespace std;

class CentaurCompany {
  static const int N = 40;
  int n;
  std::vector<int> adj[N];
  double f[N][N][N][2];
  void merge(double p[][N][2], double q[][N][2]) {
    static double res[N][N][2];
    memset(res, 0, sizeof res);
    // x : number of nodes
    // y : number of components
    // z : whether the root is selected
    for (int x1 = 0; x1 <= n; ++x1) {
      for (int y1 = 0; y1 <= x1; ++y1) {
        for (int z1 = 0; z1 < 2; ++z1) {
          double cur = p[x1][y1][z1];
          if (cur == 0.) continue;
          for (int x2 = 0; x1 + x2 <= n; ++x2) {
            for (int y2 = 0; y2 <= x2; ++y2) {
              for (int z2 = 0; z2 < 2; ++z2) {
                double t = cur * q[x2][y2][z2];
                if (t == 0.) continue;
                int x = x1 + x2;
                int y = y1 + y2 - (z1 && z2);
                int z = z1;
                res[x][y][z] += t;
              }
            }
          }
        }
      }
    }
    memcpy(p, res, sizeof res);
  }
  void dfs(int a, int fa = -1) {
    f[a][0][0][0] = f[a][1][1][1] = .5;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      if (b != fa) {
        dfs(b, a);
        merge(f[a], f[b]);
      }
    }
  }
 public:
  double getvalue(vector<int> a, vector<int> b) {
    n = a.size() + 1;
    for (int i = 0; i < n - 1; ++i) adj[a[i]].push_back(b[i]), adj[b[i]].push_back(a[i]);
    memset(f, 0, sizeof f);
    dfs(1);
    double res = 0.;
    for (int x = 0; x <= n; ++x) {
      for (int y = 0; y <= x; ++y) {
        double cur = f[1][x][y][0] + f[1][x][y][1];
        res += cur * std::max(0, 2 * (y - 1) - x); // the cost
      }
    }
    res *= 2.;
    return res;
  }
};
