#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10;

namespace Flow { // min cost flow, used for maximum weight matching in bipartite graphs

const int V = N, E = 10 * V * V, INF = 0x3f3f3f3f;

int n, s, t;

int adj[V], to[E], next[E], cap[E], cost[E], cnt;

inline void clear(int size) {
  n = size;
  s = n, t = n + 1;
  for (int i = 0; i <= t; ++i) adj[i] = 0;
  cnt = 2;
}

inline void link(int a, int b, int c, int d) {
  to[cnt] = b, next[cnt] = adj[a], cap[cnt] = c, cost[cnt] = d, adj[a] = cnt++;
  to[cnt] = a, next[cnt] = adj[b], cap[cnt] = 0, cost[cnt] = -d, adj[b] = cnt++;
}

int dist[V], cur;

typedef std::pair<int, int> Info;

bool dijkstra() {
  static Info heap[10 * E];
  for (int i = 0; i <= t; ++i) dist[i] = -INF;
  int top = 1;
  heap[1] = Info(dist[s] = 0, s);
  while (top) {
    std::pop_heap(heap + 1, heap + top + 1);
    Info info = heap[top--];
    int a = info.second;
    if (info.first < dist[a]) continue;
    for (int i = adj[a]; i; i = next[i]) {
      int b = to[i];
      if (cap[i] && dist[a] + cost[i] > dist[b]) {
        heap[++top] = Info(dist[b] = dist[a] + cost[i], b);
        std::push_heap(heap + 1, heap + top + 1);
      }
    }
  }
  if (dist[t] == -INF) return false;
  cur += dist[t];
  for (int a = 0; a <= t; ++a)
    for (int i = adj[a]; i; i = next[i])
      cost[i] -= dist[to[i]] - dist[a];
  return true;
}

int tag[V], tot;

int dfs(int a, int df) {
  if (a == t) return df;
  tag[a] = tot;
  int res = 0;
  for (int i = adj[a]; i; i = next[i]) {
    int b = to[i];
    if (tag[b] != tot && cap[i] && !cost[i]) {
      int f = dfs(b, std::min(df - res, cap[i]));
      cap[i] -= f;
      cap[i ^ 1] += f;
      res += f;
    }
    if (res == df) break;
  }
  return res;
}

int flow() {
  cur = 0;
  int res = 0;
  while (dijkstra()) {
    if (cur <= 0) break;
    do {
      ++tot;
      int f = dfs(s, INF);
      if (!f) break;
      res += cur * f;
    } while (1);
  }
  return res;
}

}

class DeerInZooDivOne {
  int adj[N], to[2 * N], next[2 * N], cnt;
  inline void link(int a, int b) {
    to[cnt] = b;
    next[cnt] = adj[a];
    adj[a] = cnt++;
  }
  int n;
  int anc[N];
  int find(int x) { return anc[x] == x ? x : (anc[x] = find(anc[x])); }
  int f[N][N];
  int fa[N], dis[N];
  std::vector<int> son[N];
  void dfs(int a) {
    for (int i = adj[a]; i; i = next[i]) {
      int b = to[i];
      if (b != fa[a]) {
        fa[b] = a;
        son[a].push_back(b);
        dfs(b);
      }
    }
  }
  void calc(int u, int v) {
    if (f[u][v]) return;
    for (int i = 0; i < son[u].size(); ++i)
      for (int j = 0; j < son[v].size(); ++j)
        calc(son[u][i], son[v][j]);
    int p = son[u].size(), q = son[v].size();
    Flow::clear(p + q);
    for (int i = 0; i < p; ++i) Flow::link(Flow::s, i, 1, 0);
    for (int i = 0; i < q; ++i) Flow::link(i + p, Flow::t, 1, 0);
    for (int i = 0; i < p; ++i)
      for (int j = 0; j < q; ++j)
        Flow::link(i, j + p, 1, f[son[u][i]][son[v][j]]);
    f[u][v] = Flow::flow() + 1; // maximum weight bipartite matching
  }
  int solve(int u, int v) {
    for (int i = 1; i <= n; ++i) son[i].clear();
    memset(f, 0, sizeof f);
    fa[u] = fa[v] = 0;
    dfs(u), dfs(v);
    calc(u, v);
    return f[u][v];
  }
 public:
  int getmax(vector<int> a, vector<int> b) {
    n = a.size() + 1;
    for (int i = 0; i < n - 1; ++i) ++a[i], ++b[i];
    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
      // enumerate the edge to cut
      cnt = 2;
      for (int j = 1; j <= n; ++j) anc[j] = j, adj[j] = 0;
      for (int j = 0; j < n - 1; ++j) {
        if (j != i) {
          anc[find(a[j])] = find(b[j]);
          link(a[j], b[j]);
          link(b[j], a[j]);
        }
      }
      for (int a = 1; a <= n; ++a)
        for (int b = a + 1; b <= n; ++b)
          if (find(a) != find(b)) ans = std::max(ans, solve(a, b)); // enumerate one of the pairings
    }
    return ans;
  }
};
