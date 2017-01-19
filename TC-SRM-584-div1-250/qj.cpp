#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, INF = 0x3f3f3f3f;

class Egalitarianism {
  int dist[N][N];
  void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  int maxDifference(vector<string> a, int d) {
    memset(dist, 0x3f, sizeof dist);
    const int n = a.size();
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (a[i][j] == 'Y') check(dist[i][j], d), check(dist[j][i], d); // |d_i - d_j| <= d
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          check(dist[i][j], dist[i][k] + dist[k][j]);
    int res = 0;
    for (int i = 0; i < n; ++i) res = std::max(res, *std::max_element(dist[i], dist[i] + n)); // calculate maximal answer
    return res == INF ? -1 : res;
  }
};
