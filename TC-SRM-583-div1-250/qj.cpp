#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10;

class TravelOnMars {
  int dist[N][N];
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  int minTimes(vector<int> r, int s, int t) {
    const int n = r.size();
    // build the graph
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int d = (i - j + n) % n;
        if (d <= r[i] || n - d <= r[i]) check(dist[i][j], 1);
      }
    }
    // floyd
    for (int i = 0; i < n; ++i) check(dist[i][i], 0);
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          check(dist[i][j], dist[i][k] + dist[k][j]);
    return dist[s][t];
  }
};
