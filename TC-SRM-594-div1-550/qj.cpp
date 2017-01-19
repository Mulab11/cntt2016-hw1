#include <bits/stdc++.h>

using namespace std;

const int N = 2500 + 10, E = 100 * N, INF = 0x3f3f3f3f;

class Flow { // a packaged network flow template
  int adj[N], to[E], next[E], cap[E], cnt;
  int h[N], gap[N], s, t;
  int dfs(int a, int df) {
    if (a == t) return df;
    int res = 0;
    for (int i = adj[a]; i; i = next[i]) {
      int b = to[i];
      if (cap[i] && h[a] == h[b] + 1) {
        int f = dfs(b, std::min(df - res, cap[i]));
        cap[i] -= f;
        cap[i ^ 1] += f;
        res += f;
      }
      if (res == df) return res;
    }
    if (--gap[h[a]] == 0) h[s] = t + 1;
    ++gap[++h[a]];
    return res;
  }
 public:
  inline void clear(int _s, int _t) {
    cnt = 2, s = _s, t = _t;
    memset(adj, 0, sizeof adj);
  }
  inline void link(int a, int b, int c) {
    to[cnt] = b, next[cnt] = adj[a], cap[cnt] = c, adj[a] = cnt++;
    to[cnt] = a, next[cnt] = adj[b], cap[cnt] = 0, adj[b] = cnt++;
  }
  int flow() {
    memset(h, 0, sizeof h);
    memset(gap, 0, sizeof gap);
    int res = 0;
    while (h[s] < t + 1) res += dfs(s, INF);
    return res;
  }
};

class FoxAndGo3 {
  Flow flow;
 public:
  int maxEmptyCells(vector<string> board) {
    const int n = board.size();
    const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
    const int s = n * n + 1, t = s + 1;
    flow.clear(s, t);
    int res = 0;
    // first we 2-color the chessboard
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == 'x') continue;
        ++res;
        int p = i * n + j;
        if ((i + j) & 1) flow.link(s, p, 1); else flow.link(p, t, 1);
        // cutting this edge means we decide not to remove the white piece here / we decide to put a black piece at the space
        if (board[i][j] == 'o') {
          for (int k = 0; k < 4; ++k) {
            int x = i + dx[k], y = j + dy[k];
            if (0 <= x && x < n && 0 <= y && y < n && board[x][y] == '.') {
              int q = x * n + y;
              if ((i + j) & 1) flow.link(p, q, INF); else flow.link(q, p, INF);
            }
          }
          // if (i, j) is surrounded by black pieces, we can remove the white piece here, that is, not to cut the edge
        }
      }
    }
    return res - flow.flow(); // maximal possible space remaining
  }
};
