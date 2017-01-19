#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

class GameInDarknessDiv1 {
  int n, m;
  std::vector<std::string> a;
  int dist[3][N][N], mask[3][N][N];
  void bfs(int id, int u, int v) {
    // breadth first search
    // calculate the distance from (u, v) to each node
    static int q[2 * N * N];
    int r = 0;
    q[r++] = u;
    q[r++] = v;
    for (int i = 0; i < n; ++i) std::fill(dist[id][i], dist[id][i] + m, -1);
    for (int i = 0; i < n; ++i) std::fill(mask[id][i], mask[id][i] + m, 0);
    dist[id][u][v] = 0;
    for (int f = 0; f < r; f += 2) {
      int x = q[f], y = q[f + 1];
      for (int k = 0; k < 4; ++k) {
        int a = x + dx[k], b = y + dy[k];
        if (0 <= a && a < n && 0 <= b && b < m && this->a[a][b] != '#' && dist[id][a][b] == -1) {
          dist[id][a][b] = dist[id][x][y] + 1;
          mask[id][a][b] = (mask[id][x][y] ? mask[id][x][y] : (1 << k));
          q[r++] = a;
          q[r++] = b;
        }
      }
    }
  }
 public:
  string check(vector<string> _a) {
    a = _a;
    n = a.size(), m = a[0].length();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (a[i][j] == 'A') bfs(0, i, j); else if (a[i][j] == 'B') bfs(1, i, j);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] != '#' && dist[0][i][j] - dist[1][i][j] >= 2) {
          bfs(2, i, j);
          int cur = 0;
          for (int x = 0; x < n; ++x)
            for (int y = 0; y < m; ++y)
              if (dist[2][x][y] > 2) cur |= mask[2][x][y];
          if (__builtin_popcount(cur) > 2) return "Bob wins";
        }
      }
    }
    return "Alice wins";
  }
};
