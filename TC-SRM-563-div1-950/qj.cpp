#include <bits/stdc++.h>

using namespace std;

typedef unsigned char u8;

const int N = 40 + 10, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1}, MOD = 1000000009;

class CoinsGame {
  int n, m;
  std::vector<std::string> a;
  inline bool check(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }
  inline int pos(int x, int y) { return x * m + y; }
  int anc[N * N], size[N * N];
  int find(int x) { return anc[x] == x ? x : (anc[x] = find(anc[x])); }
  void meld(int x, int y) {
    if ((x = find(x)) == (y = find(y))) return;
    anc[x] = y;
    size[y] += size[x];
  }
  bool flag[N][N][N][N];
  std::vector<u8> q;
  void push(int x0, int y0, int x1, int y1) {
    if (flag[x0][y0][x1][y1]) return;
    flag[x0][y0][x1][y1] = true;
    q.push_back(x0);
    q.push_back(y0);
    q.push_back(x1);
    q.push_back(y1);
  }
  void expand(int x0, int y0, int x1, int y1) {
    int x[] = {x0, x1}, y[] = {y0, y1};
    for (int k = 0; k < 4; ++k) {
      for (int s = 1; s < 4; ++s) {
        int p[2], q[2];
        for (int i = 0; i < 2; ++i) {
          if (s >> i & 1) {
            int u = x[i] - dx[k], v = y[i] - dy[k];
            if (!check(u, v) || a[u][v] == '#') goto fail;
            p[i] = u, q[i] = v;
          } else {
            int u = x[i] + dx[k], v = y[i] + dy[k];
            if (!check(u, v) || a[u][v] == '.') goto fail;
            p[i] = x[i], q[i] = y[i];
          }
        }
        push(p[0], q[0], p[1], q[1]);
     fail:
        continue;
      }
    }
  }
  int mem[N * N];
 public:
  int ways(vector<string> _a) {
    // flag[x1][y1][x2][y2] : whether (x1, y1) and (x2, y2) are equivalent
    a = _a;
    n = a.size(), m = a[0].length();
    for (int x0 = 0; x0 < n; ++x0) {
      for (int y0 = 0; y0 < m; ++y0) {
        if (a[x0][y0] == '#') continue;
        for (int x1 = 0; x1 < n; ++x1) {
          for (int y1 = 0; y1 < m; ++y1) {
            if (a[x1][y1] == '#') continue;
            for (int k = 0; k < 4; ++k) {
              if (check(x0 + dx[k], y0 + dy[k]) != check(x1 + dx[k], y1 + dy[k])) {
                push(x0, y0, x1, y1);
                break;
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < q.size(); i += 4) expand(q[i], q[i + 1], q[i + 2], q[i + 3]); // bfs
    mem[0] = 1;
    for (int i = 1; i < N * N; ++i) mem[i] = 2LL * mem[i - 1] % MOD;
    int res = 0;
    for (int i = 0; i < n; ++i) res += std::count(a[i].begin(), a[i].end(), '.');
    res = mem[res] - 1;
    for (int i = 0; i < n * m; ++i) size[anc[i] = i] = 1;
    for (int x0 = 0; x0 < n; ++x0) {
      for (int y0 = 0; y0 < m; ++y0) {
        if (a[x0][y0] == '#') continue;
        for (int x1 = 0; x1 < n; ++x1) {
          for (int y1 = 0; y1 < m; ++y1) {
            if (a[x1][y1] == '#') continue;
            if (!flag[x0][y0][x1][y1]) meld(pos(x0, y0), pos(x1, y1)); // meld the equivalent classes
          }
        }
      }
    }
    for (int x = 0; x < n; ++x)
      for (int y = 0; y < m; ++y)
        if (a[x][y] == '.' && find(pos(x, y)) == pos(x, y)) res = (res - (mem[size[pos(x, y)]] - 1)) % MOD; // subtract the illegal solutions
    return (res + MOD) % MOD;
  }
};
