#include <bits/stdc++.h>

const int N = 20 + 1, V = N * N * 2, E = V * 10;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1}, INF = 10000;

int n, m, cost[N][N], benefit[N][N];

inline int parser(char ch) {
  if (isdigit(ch)) return ch - '0';
  if (islower(ch)) return ch - 'a' + 10;
  return ch - 'A' + 36;
}

int adj[V];
int to[E], next[E], cap[E];

inline void link(int a, int b, int c) {
  static int cnt = 2;
  to[cnt] = b, next[cnt] = adj[a], cap[cnt] = c, adj[a] = cnt++;
  to[cnt] = a, next[cnt] = adj[b], cap[cnt] = 0, adj[b] = cnt++;
}

int s, t, h[V], gap[V];

int DFS(int a, int df) {
  if (a == t) return df;
  int tot = 0;
  for (int it = adj[a]; it; it = next[it]) {
    int b = to[it];
    if (cap[it] && h[a] == h[b] + 1) {
      int f = DFS(b, std::min(cap[it], df - tot));
      cap[it] -= f;
      cap[it ^ 1] += f;
      tot += f;
    }
    if (tot == df) return tot;
  }
  if (--gap[h[a]] == 0) h[s] = t + 1;
  ++gap[++h[a]];
  return tot;
}

inline int flow() {
  memset(h, 0, sizeof h);
  memset(gap, 0, sizeof gap);
  int res = 0;
  while (h[s] < t + 1) res += DFS(s, INF);
  return res;
}

class SurroundingGame {
 public:
  int maxScore(std::vector<std::string> a, std::vector<std::string> b) {
    n = a.size();
    m = a[0].length();
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cost[i][j] = parser(a[i][j]);
        sum += (benefit[i][j] = parser(b[i][j]));
      }
    }
    s = 2 * n * m, t = 2 * n * m + 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int a = i * m + j, b = a + n * m;
        link(a, b, benefit[i][j]);
        if ((i + j) & 1) {
          link(s, a, cost[i][j]);
          for (int k = 0; k < 4; ++k) {
            int x = i + dx[k], y = j + dy[k];
            if (0 <= x && x < n && 0 <= y && y < m) {
              int c = x * m + y, d = c + n * m;
              link(a, c, INF);
              link(b, d, INF);
            }
          }
        } else {
          link(b, t, cost[i][j]);
        }
      }
    }
    return sum - flow();
  }
};
