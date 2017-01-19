#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class CirclesGame {
  inline i64 sqr(i64 x) { return x * x; }
  struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y): x(_x), y(_y) {}
    inline bool operator< (const Point &rhs) const {
      return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
  };
  inline i64 dist2(const Point &a, const Point &b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }
  static const int N = 50 + 10;
  int fa[N], sg[N], size[N];
  std::vector<int> adj[N], pool[N];
  void dfs(int a) {
    pool[a].push_back(a);
    size[a] = 1;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      dfs(b);
      size[a] += size[b];
      std::copy(pool[b].begin(), pool[b].end(), std::back_inserter(pool[a]));
    }
  }
  int solve(int a) {
    // then calculate sg[i]
    if (sg[a] != -1) return sg[a];
    std::set<int> cur;
    for (int i = 0; i < pool[a].size(); ++i) {
      int val = 0;
      for (int b = pool[a][i], c = -1;; c = b, b = fa[b]) {
        for (int j = 0; j < adj[b].size(); ++j) {
          int d = adj[b][j];
          if (d != c) val ^= solve(d);
        }
        if (b == a) break;
      }
      cur.insert(val);
    }
    for (int i = 0;; ++i) if (!cur.count(i)) return sg[a] = i;
  }
 public:
  string whoCanWin(vector<int> x, vector<int> y, vector<int> r) {
    const int n = x.size();
    std::vector< std::pair<int, Point> > p;
    for (int i = 0; i < n; ++i) p.push_back(std::make_pair(r[i], Point(x[i], y[i])));
    std::sort(p.begin(), p.end());
    // construct the tree
    memset(fa, -1, sizeof fa);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (dist2(p[i].second, p[j].second) <= sqr(p[i].first - p[j].first)) {
          fa[i] = j;
          break;
        }
      }
    }
    for (int i = 0; i < n; ++i) if (fa[i] != -1) adj[fa[i]].push_back(i);
    for (int i = 0; i < n; ++i) if (fa[i] == -1) dfs(i);
    memset(sg, -1, sizeof sg);
    int res = 0;
    for (int i = 0; i < n; ++i) if (fa[i] == -1) res ^= solve(i);
    return res ? "Alice" : "Bob";
  }
};
