#include <bits/stdc++.h>

using namespace std;

class DrawingPointsDivOne {
  static const int INF = 153, N = 300;
 public:
  int maxSteps(vector<int> x, vector<int> y) {
    const int n = x.size();
    for (int i = 0; i < n; ++i) x[i] += 70, y[i] += 70;
    int l = 1, r = INF;
    while (l < r) {
      // binary search the answer
      int mid = (l + r + 1) / 2;
      static int cur[N][N];
      memset(cur, 0, sizeof cur);
      for (int i = 0; i < n; ++i)
        for (int a = 0; a < mid; ++a)
          ++cur[x[i] + a][y[i]], --cur[x[i] + a][y[i] + mid];
      for (int i = 0; i < N; ++i)
        for (int j = 1; j < N; ++j)
          cur[i][j] += cur[i][j - 1];
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
          cur[i][j] = (cur[i][j] > 0);
      for (int i = N - 2; i >= 0; --i)
        for (int j = N - 2; j >= 0; --j)
          cur[i][j] += cur[i][j + 1] + cur[i + 1][j] - cur[i + 1][j + 1];
      int cnt = 0;
      for (int i = 0; i + mid < N; ++i)
        for (int j = 0; j + mid < N; ++j)
          cnt += (cur[i][j] - cur[i + mid][j] - cur[i][j + mid] + cur[i + mid][j + mid] == mid * mid);
      if (cnt > n) r = mid - 1; else l = mid; // check if legal
    }
    return l == INF ? -1 : (l - 1);
  }
};
