#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class TheBrickTowerHardDivOne {
  static const int N = 130;
  static const i64 MOD = 1234567891;
  int n, m;
  inline int pos(int x, int y) { return x * (m + 1) + y; }
  int cnt;
  std::map<std::vector<int>, int> pool;
  std::vector<int> cur;
  int count(const std::vector<int> &a) {
    return (a[0] == a[1]) + (a[0] == a[2]) + (a[1] == a[3]) + (a[2] == a[3]);
  }
  int calc(const std::vector<int> &a, const std::vector<int> &b) {
    return (a[0] == b[0]) + (a[1] == b[1]) + (a[2] == b[2]) + (a[3] == b[3]);
  }
  void compress(std::vector<int> &a) {
    std::vector<int> id(10, -1);
    int tot = 0;
    for (int i = 0; i < a.size(); ++i) if (id[a[i]] == -1) id[a[i]] = tot++;
    for (int i = 0; i < a.size(); ++i) a[i] = id[a[i]];
  }
  i64 trans[N][N], init[N];
  void dfs4(int i, int j) {
    // search all possible patterns
    if (i == 4) {
      pool[cur] = ++cnt;
      int c = count(cur);
      if (c > m) return;
      i64 &t = init[pos(cnt, count(cur))] = 1;
      for (int k = j; k >= 0; --k) (t *= (n - k)) %= MOD;
      for (int k = 0; k <= m; ++k) ++trans[pos(cnt, k)][N - 1];
      return;
    }
    for (int k = 0; k <= j; ++k) cur[i] = k, dfs4(i + 1, j);
    dfs4(i + 1, cur[i] = ++j);
  }
  void dfs8(int i, int j) {
    // search all possible trans
    if (i == 8) {
      std::vector<int> p(cur.begin(), cur.begin() + 4), q(cur.begin() + 4, cur.end());
      int z = calc(p, q) + count(q);
      compress(q);
      int x = pool[p], y = pool[q];
      i64 coef = 1;
      for (int k = *std::max_element(p.begin(), p.end()) + 1; k <= j; ++k) (coef *= (n - k)) %= MOD;
      for (int k = 0; k + z <= m; ++k) (trans[pos(x, k)][pos(y, k + z)] += coef) %= MOD;
      return;
    }
    for (int k = 0; k <= j; ++k) cur[i] = k, dfs8(i + 1, j);
    dfs8(i + 1, cur[i] = ++j);
  }
  void mul(i64 lhs[][N], const i64 rhs[][N]) {
    static i64 res[N][N];
    memset(res, 0, sizeof res);
    for (int i = 0; i < N; ++i)
      for (int k = 0; k < N; ++k)
        for (int j = 0; j < N; ++j)
          (res[i][j] += lhs[i][k] * rhs[k][j]) %= MOD;
    memcpy(lhs, res, sizeof res);
  }
  void power(i64 base[][N], i64 exp) {
    static i64 res[N][N];
    memset(res, 0, sizeof res);
    for (int i = 0; i < N; ++i) res[i][i] = 1;
    for (; exp; exp >>= 1) {
      if (exp & 1) mul(res, base);
      mul(base, base);
    }
    memcpy(base, res, sizeof res);
  }
 public:
  int find(int c, int k, i64 h) {
    n = c, m = k;
    memset(trans, 0, sizeof trans);
    memset(init, 0, sizeof init);
    trans[N - 1][N - 1] = 1;
    cur.resize(4);
    cnt = 0;
    dfs4(0, -1);
    cur.resize(8);
    dfs8(0, -1);
    power(trans, h);
    i64 res = 0;
    for (int i = 0; i < N; ++i) (res += init[i] * trans[i][N - 1]) %= MOD;
    return res;
  }
};
