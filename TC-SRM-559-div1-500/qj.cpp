#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class HatRack {
  static const int N = 50 + 10;
  int n;
  std::vector<int> adj[N];
  i64 f[N][N], g[N][N];
  int size[N][N];
  void dfs(int a, int fa) {
    int &s = size[a][fa];
    if (s != -1) return;
    s = 1;
    i64 &x = f[a][fa] = 0, &y = g[a][fa] = 0;
    std::vector<int> p, q;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      if (b == fa) continue;
      dfs(b, a);
      p.push_back(b);
      q.push_back(size[b][a]);
      s += size[b][a];
    }
    // check if the two subtrees are both perfect binary trees
    if (p.size() > 2) return;
    if (p.empty()) {
      y = 1;
      return;
    }
    if (p.size() == 1) {
      x = (s == 2);
      return;
    }
    if (q[0] < q[1]) std::swap(p[0], p[1]), std::swap(q[0], q[1]);
    if (q[0] > 2 * q[1] + 1) return;
    if (q[0] == q[1]) {
      y = 2 * g[p[0]][a] * g[p[1]][a];
      return;
    }
    y = 0;
    x = f[p[0]][a] * g[p[1]][a] + g[p[0]][a] * (f[p[1]][a] + g[p[1]][a]);
  }
 public:
  i64 countWays(vector<int> a, vector<int> b) {
    n = a.size() + 1;
    for (int i = 0; i < n - 1; ++i) adj[a[i]].push_back(b[i]), adj[b[i]].push_back(a[i]);
    memset(size, -1, sizeof size);
    i64 res = 0;
    for (int i = 1; i <= n; ++i) dfs(i, 0), res += f[i][0] + g[i][0];
    return res;
  }
};
