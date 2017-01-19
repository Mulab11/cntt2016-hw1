#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 5000 + 10, E = 100 * N, INF = 10 * E;

class MCMF { // min cost flow
  int arc[N], adj[N], to[E], next[E], cap[E], cost[E], cnt;
  int s, t, cur;
  int dist[N];
  std::pair<int, int> heap[E];
  bool dijkstra() {
    std::fill(dist, dist + t + 1, INF);
    int top = 1;
    for (heap[0] = std::make_pair(dist[s] = 0, s); top;) {
      std::pop_heap(heap, heap + top);
      std::pair<int, int> info = heap[--top];
      int a = info.second;
      if (-info.first > dist[a]) continue;
      for (int i = adj[a]; i; i = next[i]) {
        int b = to[i], c = cost[i];
        if (cap[i] && dist[a] + c < dist[b]) {
          heap[top++] = std::make_pair(-(dist[b] = dist[a] + c), b);
          std::push_heap(heap, heap + top);
        }
      }
    }
    if (dist[t] == INF) return false;
    for (int a = 0; a <= t; ++a)
      for (int i = adj[a]; i; i = next[i])
        cost[i] -= dist[to[i]] - dist[a];
    cur += dist[t];
    return true;
  }
  int tag[N], tot;
  int dfs(int a, int df) {
    if (a == t) return df;
    tag[a] = tot;
    int res = 0;
    for (int &i = arc[a]; i; i = next[i]) {
      int b = to[i];
      if (cap[i] && !cost[i] && tag[b] != tot) {
        int f = dfs(b, std::min(df - res, cap[i]));
        cap[i] -= f;
        cap[i ^ 1] += f;
        res += f;
      }
      if (res == df) break;
    }
    return res;
  }
 public:
  inline void clear(int _s, int _t) {
    cnt = 2, s = _s, t = _t;
    memset(adj, 0, sizeof adj);
  }
  inline void link(int a, int b, int c, int d) {
    to[cnt] = b, next[cnt] = adj[a], cap[cnt] = c, cost[cnt] = d, adj[a] = cnt++;
    to[cnt] = a, next[cnt] = adj[b], cap[cnt] = 0, cost[cnt] = -d, adj[b] = cnt++;
  }
  std::pair<int, int> flow() {
    std::pair<int, int> res(0, 0);
    for (cur = 0; dijkstra();) {
      std::copy(adj, adj + t + 1, arc);
      do {
        ++tot;
        int f = dfs(s, INF);
        if (!f) break;
        res.first += f;
        res.second += cur * f;
      } while (1);
    }
    return res;
  }
};

class CurvyonRails {
  MCMF g;
  int n, m;
  inline int pos(int x, int y) { return x * m + y; }
 public:
  int getmin(vector<string> a) {
    n = a.size(), m = a[0].length();
    const int tot = n * m, s = 2 * tot, t = s + 1;
    g.clear(s, t);
    const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == 'w') continue;
        // the cost of changing direction
        g.link(pos(i, j), pos(i, j) + tot, INF, a[i][j] == 'C');
        g.link(pos(i, j) + tot, pos(i, j), INF, a[i][j] == 'C');
        if ((i + j) & 1) {
          // bicoloring
          g.link(pos(i, j), t, 1, 0);
          g.link(pos(i, j) + tot, t, 1, 0);
          continue;
        }
        g.link(s, pos(i, j), 1, 0);
        g.link(s, pos(i, j) + tot, 1, 0);
        cnt += 2;
        for (int k = 0; k < 4; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (0 <= x && x < n && 0 <= y && y < m && a[x][y] != 'w') {
            int temp = (k & 1) ? tot : 0;
            g.link(pos(i, j) + temp, pos(x, y) + temp, 1, 0);
          }
        }
      }
    }
    std::pair<int, int> res = g.flow();
    return res.first == cnt ? res.second : -1;
  }
};
